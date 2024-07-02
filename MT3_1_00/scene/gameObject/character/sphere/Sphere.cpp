﻿#include "Sphere.h"
#include "scene/gameObject/camera/Camera.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <numbers>
#define pi_f numbers::pi_v<float>
using namespace std;

Sphere::Sphere() {
	sphere_ = {};//スフィアの素材
	sphere_.color = WHITE;//色

	screenA_ = {};//スクリーン座標
	screenB_ = {};//スクリーン座標
	screenC_ = {};//スクリーン座標
}

Sphere::~Sphere() {
}

//初期化
void Sphere::Initialize(Material sphere) {
	sphere_ = sphere;
	scale_ = { 1.0f,1.0f,1.0f };
}

//更新処理
void Sphere::Update() {
	translate_ = sphere_.center;

}

//デバックテキスト
void Sphere::DebugText(const char* label_center, const char* label_radius, const char* label_Rotate) {
	ImGui::DragFloat3(label_Rotate, &rotate_.x, 0.1f);
	ImGui::DragFloat3(label_center, &sphere_.center.x, 0.01f);
	ImGui::DragFloat(label_radius, &sphere_.radius, 0.01f);
}

//描画
void Sphere::Draw(const Matrix4x4& viewProjection, const Matrix4x4& viewprotMatirx) {
	const uint32_t kSubdivision = 16;//分割数
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
				sphere_.center.x + sphere_.radius * cos(lat) * cos(lon + kLonEvery),
				sphere_.center.y + sphere_.radius * sin(lat),
				sphere_.center.z + sphere_.radius * cos(lat) * sin(lon + kLonEvery)
			};

			//スクリーン座標を求める
			ScreenTransform(viewProjection, viewprotMatirx, a, screenA_);
			ScreenTransform(viewProjection, viewprotMatirx, b, screenB_);
			ScreenTransform(viewProjection, viewprotMatirx, c, screenC_);

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




//当たり判定(球と球)
void Sphere::IsCollision(const Material& sphere, const Vector3& worldPosition) {
	Vector3 worldVector = { worldMatrix_.m[3][0],worldMatrix_.m[3][1],worldMatrix_.m[3][2] };
	float distance = Math::Length(worldVector - worldPosition);
	if (distance <= (sphere_.radius / 2.0f) + (sphere.radius / 2.0f)) {
		sphere_.isHit = true;
	}
	else {
		sphere_.isHit = false;
	}
	ChangeColor();//色を変える
}

//カラーのセッター
void Sphere::SetColor(uint32_t color) {
	sphere_.color = color;
}

//スフィアの素材のゲッター
Sphere::Material Sphere::GetSphereMaterial() {
	return sphere_;
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
