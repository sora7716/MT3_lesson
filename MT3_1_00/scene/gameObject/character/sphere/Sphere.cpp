#include "Sphere.h"
#include "scene/gameObject/camera/Camera.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <numbers>
#define pi numbers::pi_v<float>
using namespace std;

void Sphere::Initialize(Camera* camera){
	camera_ = camera;
	center_ = {0.0f,-40,162};
	radius_ = 30;
}

void Sphere::DebugText(){
	ImGui::DragFloat3("center", &center_.x, 0.1f);
}

void Sphere::Draw() {
	const uint32_t kSubdivision = 12;//分割数
	const float kLatEvery  = pi/float(kSubdivision);//経度分割1つ分の角度(θd)
	const float kLonEvery  = 2.0f*pi/float(kSubdivision);//緯度分割1つ分の角度(φd)

	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++) {
		float lat = -float(pi) / 2.0f + kLatEvery * latIndex;//θ
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//φ
			Vector3 a, b, c;//ローカル座標
			a = {
				center_.x+radius_*cos(lat) * cos(lon),
				center_.y+radius_*sin(lat),
				center_.z+radius_*cos(lat) * sin(lon)
			};

			b = {
				center_.x+radius_*cos(lat + kLatEvery) * cos(lon),
				center_.y+radius_*sin(lat + kLatEvery),
				center_.z+radius_*cos(lat + kLatEvery) * sin(lon)
			};

			c = {
				center_.x+radius_*cos(lat) * cos(lon + kLonEvery),
				center_.y+radius_*sin(lat),
				center_.z+radius_*cos(lat) * sin(lon + kLonEvery)
			};
			//スクリーン座標を求める
			screenA_ = Math::Transform(Math::Transform(a, camera_->GetViewProjectionMatrix()),camera_->GetViewportMatrix());
			screenB_ = Math::Transform(Math::Transform(b, camera_->GetViewProjectionMatrix()),camera_->GetViewportMatrix());
			screenC_ = Math::Transform(Math::Transform(c, camera_->GetViewProjectionMatrix()),camera_->GetViewportMatrix());

			//縦の線の描画
			Novice::DrawLine(
				(int)screenA_.x, (int)screenA_.y,
				(int)screenB_.x, (int)screenB_.y,
				BLACK
			);
			//横の線の描画
			Novice::DrawLine(
				(int)screenA_.x, (int)screenA_.y,
				(int)screenC_.x, (int)screenC_.y,
				BLACK
			);
		}
	}

}