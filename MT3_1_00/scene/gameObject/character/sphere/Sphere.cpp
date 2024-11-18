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
void Sphere::Initialize(Camera* camera, const SphereMaterial&& sphereMaterial) {
	sphere_ = sphereMaterial;
	scale_ = { 1.0f,1.0f,1.0f };
	SetCamera(camera);
}

//更新処理
void Sphere::Update() {
	//theta_ += 0.1f;
	//lissajousPos_ = { sqrt(2.0f) * theta_ + pi_f / 6.0f,theta_ + pi_f / 4.0f,2.0f * theta_ };
	//// sphereの中心をリサージュ曲線上に移動させる
	//sphere_.center = Math::LissajousCurve(lissajousPos_, lissajousCenter_, { 2.0f,1.0f,1.0f });
}

#ifdef _DEBUG
//デバックテキスト
void Sphere::DebugText(const char* name) {
	string rotateLabel = string(name) + ".rotate";
	ImGui::DragFloat3(rotateLabel.c_str(), &rotate_.x, 0.1f);

	string centerLabel = string(name) + ".center";
	ImGui::DragFloat3(centerLabel.c_str(), &sphere_.center.x, 0.01f);

	string radiusLabel = string(name) + ".radius";
	ImGui::DragFloat(radiusLabel.c_str(), &sphere_.radius, 0.01f);

	/*ImGui::DragFloat3("ce", &lissajousCenter_.x, 0.1f);*/
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
				sphere_.radius * cos(lat) * cos(lon),
				sphere_.radius * sin(lat),
				sphere_.radius * cos(lat) * sin(lon)
			};

			b = {
				sphere_.radius * cos(lat + kLatEvery) * cos(lon),
				sphere_.radius * sin(lat + kLatEvery),
				sphere_.radius * cos(lat + kLatEvery) * sin(lon)
			};

			c = {
				sphere_.radius * cos(lat + kLatEvery) * cos(lon + kLonEvery),
				sphere_.radius * sin(lat + kLatEvery),
				sphere_.radius * cos(lat + kLatEvery) * sin(lon + kLonEvery)
			};
			//スクリーン座標を求める
			screenA_ = ScreenTransform(camera_, a, rotate_,sphere_.center);
			screenB_ = ScreenTransform(camera_, b, rotate_,sphere_.center);
			screenC_ = ScreenTransform(camera_, c, rotate_,sphere_.center);

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
void Sphere::OnCollision(bool isHit) {
	sphere_.isHit = isHit;
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
