#include "Sphere.h"
#include "scene/gameObject/camera/Camera.h"
#include "scene/gameObject/character/plane/Plane.h"
#include "scene/gameObject/character/grid/Grid.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <numbers>
#include <string>
using namespace std;

Sphere::Sphere() {
	sphere_ = {};//スフィアの素材
	sphere_.color = WHITE;//色

	screenA_ = {};//スクリーン座標
	screenB_ = {};//スクリーン座標
	screenC_ = {};//スクリーン座標
	plane_ = nullptr;
	camera_ = nullptr;
}

Sphere::~Sphere() {
}

//初期化
void Sphere::Initialize(Camera* camera,const SphereMaterial&&sphereMaterial) {
	sphere_ = sphereMaterial;
	scale_ = { 1.0f,1.0f,1.0f };
	SetCamera(camera);
}

//更新処理
void Sphere::Update() {
	translate_ = sphere_.center;
}

#ifdef _DEBUG
//デバックテキスト
void Sphere::DebugText(const char* name) {
	/*string rotateLabel = string(label) + ".rotate";
	ImGui::DragFloat3(rotateLabel.c_str(), &rotate_.x, 0.1f);*/

	string centerLabel = string(name) + ".center";
	ImGui::DragFloat3(centerLabel.c_str(), &sphere_.center.x, 0.01f);

	string radiusLabel = string(name) + ".radius";
	ImGui::DragFloat(radiusLabel.c_str(), &sphere_.radius, 0.01f);
}
#endif // _DEBUG

//描画
void Sphere::Draw() {
	const uint32_t kSubdivision = 10;//分割数
	const float kLatEvery = pi_f / float(kSubdivision);//経度分割1つ分の角度(θd)
	const float kLonEvery = 2.0f * pi_f / float(kSubdivision);//緯度分割1つ分の角度(φd)

	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++) {
		float lat = -pi_f / 2.0f + kLatEvery * latIndex;//θ
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//φ
			Vector3 a, b, c;//ローカル座標
			a = {
				sphere_.center.x + sphere_.radius * cos(lat) * cos(lon),
				sphere_.center.y + sphere_.radius * sin(lat),
				sphere_.center.z + sphere_.radius * cos(lat) * sin(lon)
			};

			b = {
				sphere_.center.x + sphere_.radius * cos(lat + kLatEvery) * cos(lon),
				sphere_.center.y + sphere_.radius * sin(lat + kLatEvery),
				sphere_.center.z + sphere_.radius * cos(lat + kLatEvery) * sin(lon)
			};

			c = {
				sphere_.center.x + sphere_.radius * cos(lat+ kLatEvery) * cos(lon + kLonEvery),
				sphere_.center.y + sphere_.radius * sin(lat+ kLatEvery),
				sphere_.center.z + sphere_.radius * cos(lat+ kLatEvery) * sin(lon + kLonEvery)
			};

			////ワールド座標系
			//worldMatrix_ = Math::MakeOBBWorldMatrix(o, sphere_.center);
			////wvpマトリックス
			//worldViewProjectionMatrix_ = worldMatrix_ * camera_->GetViewMatrix() * camera_->GetProjctionMatrix();
			//screenA_ = Math::Transform(Math::Transform(a, worldViewProjectionMatrix_), camera_->GetViewportMatrix());
			//screenB_ = Math::Transform(Math::Transform(b, worldViewProjectionMatrix_), camera_->GetViewportMatrix());
			//screenC_ = Math::Transform(Math::Transform(c, worldViewProjectionMatrix_), camera_->GetViewportMatrix());
			//translate_ = sphere_.center;
			//スクリーン座標を求める
			CameraScreenTransform(camera_,a, screenA_);
			CameraScreenTransform(camera_,b, screenB_);
			CameraScreenTransform(camera_,c, screenC_);

			//縦の線の描画
			Novice::DrawLine(
				(int)screenA_.x, (int)screenA_.y,
				(int)screenB_.x, (int)screenB_.y,
				sphere_.color
			);
			//横の線の描画
			Novice::DrawLine(
				(int)screenB_.x, (int)screenB_.y,
				(int)screenC_.x, (int)screenC_.y,
				sphere_.color
			);
		}
	}

}




//当たった時の判定
void Sphere::OnCollision() {

	ChangeColor();//色を変える
}

//カラーのセッター
void Sphere::SetColor(uint32_t color) {
	sphere_.color = color;
}

//スフィアの素材のゲッター
Sphere::SphereMaterial Sphere::GetSphereMaterial()const {
	return sphere_;
}

//平面のセッター
void Sphere::SetPlane(Plane* plane) {
	plane_ = plane;
}

//カメラのゲッター
void Sphere::SetCamera(Camera* camera) {
	camera_ = camera;
}

//球の素材のセッター
void Sphere::SetSphere(const SphereMaterial& material) {
	sphere_ = material;
}

//当たり判定のセッター
void Sphere::SetIsHit(bool isHit) {
	sphere_.isHit = isHit;
}

//色を変える
void Sphere::ChangeColor() {
	if (sphere_.isHit) {
		sphere_.color = RED;
	}
	else {
		sphere_.color = WHITE;
	}
}
