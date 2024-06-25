#include "Sphere.h"
#include "scene/gameObject/camera/Camera.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <numbers>
#define pi_f numbers::pi_v<float>
using namespace std;

Sphere::Sphere(){
	sphere_ = {};//スフィアの素材

	camera_ = nullptr;//カメラ

	screenA_ = {};//スクリーン座標
	screenB_ = {};//スクリーン座標
	screenC_ = {};//スクリーン座標
}

Sphere::~Sphere(){
}

//初期化
void Sphere::Initialize(Camera* camera, Material sphere){
	camera_ = camera;
	sphere_ = sphere;
	scale_ = { 1.0f,1.0f,1.0f };
}

//更新処理
void Sphere::Update(){
	translate_ = sphere_.center;
	WvpMatrix(camera_);
}

//デバックテキスト
void Sphere::DebugText(){
	ImGui::DragFloat3("SpherCenter", &sphere_.center.x, 0.1f);
	ImGui::DragFloat("SpherRadius", &sphere_.radius, 0.1f);
	ImGui::DragFloat3("SpherRadius", &rotate_.x, 0.1f);
}

//描画
void Sphere::Draw() {
	const uint32_t kSubdivision = 12;//分割数
	const float kLatEvery  = pi_f/float(kSubdivision);//経度分割1つ分の角度(θd)
	const float kLonEvery  = 2.0f*pi_f/float(kSubdivision);//緯度分割1つ分の角度(φd)

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
				sphere_.center.z + sphere_.radius*cos(lat + kLatEvery) * sin(lon)
			};

			c = {
				sphere_.center.x + sphere_.radius * cos(lat) * cos(lon + kLonEvery),
				sphere_.center.y + sphere_.radius * sin(lat),
				sphere_.center.z + sphere_.radius * cos(lat) * sin(lon + kLonEvery)
			};

			//スクリーン座標を求める
			ScreenTransform(camera_, a, screenA_);
			ScreenTransform(camera_, b, screenB_);
			ScreenTransform(camera_, c, screenC_);

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

//カラーのセッター
void Sphere::SetColor(uint32_t color){
	sphere_.color = color;
}
