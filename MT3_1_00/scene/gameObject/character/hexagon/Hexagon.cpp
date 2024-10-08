#include "Hexagon.h"
#include "scene/func/Math.h"
#include "imgui.h"
#include <string>
#include <cmath>
#include <numbers>
#define pi_f std::numbers::pi_v<float>
#define rad pi_f/180.0f

//初期化
void Hexagon::Initialize(Camera* camera, HexagonMaterial hexagonMaterial) {
	camera_ = camera;
	hexagon_ = hexagonMaterial;
}

//更新
void Hexagon::Update() {
	for (int i = 0; i < 6; i++) {
		float theta = 60.0f * static_cast<float>(i);
		float angle = theta * rad;
		vertex[i].x = hexagon_.radius * std::cosf(angle) + hexagon_.center.x;
		vertex[i].y = hexagon_.center.y;
		vertex[i].z = hexagon_.radius * std::sinf(angle) + hexagon_.center.z;
	}
	for (int i = 0; i < 6; i++) {
		CameraScreenTransform(camera_, vertex[i], screenVertex[i]);
	}
}

//デバックテキスト
void Hexagon::DebugText(const char* name) {
	std::string centerText = static_cast<std::string>(name) + ".center";
	ImGui::DragFloat3(centerText.c_str(), &hexagon_.center.x, 0.1f);
	std::string radiusText = static_cast<std::string>(name) + ".radius";
	ImGui::DragFloat(radiusText.c_str(), &hexagon_.radius, 0.1f);
}

//描画
void Hexagon::Draw() {
	for (int i = 1; i < 6; i++) {
		Novice::DrawLine((int)screenVertex[i - 1].x, (int)screenVertex[i - 1].y, (int)screenVertex[i].x, (int)screenVertex[i].y, hexagon_.color);
	}
	Novice::DrawLine((int)screenVertex[5].x, (int)screenVertex[5].y, (int)screenVertex[0].x, (int)screenVertex[0].y, hexagon_.color);

}

// 衝突したとき
void Hexagon::OnCollision(bool isHit) {
	if (isHit) {
		hexagon_.color = RED;
	}
	else {
		hexagon_.color = WHITE;
	}
}

//頂点のゲッター
Vector3* Hexagon::GetVertex() {
	return vertex;
}

// 六角形の素材のゲッター
GameObject::HexagonMaterial Hexagon::GetHexagonMaterial() {
	return hexagon_;
}
