#include "Hexagon.h"
#include "scene/func/Math.h"
#include "imgui.h"
#include <string>
#include <cmath>
#include <numbers>
#define rad pi_f/180.0f

//初期化
void Hexagon::Initialize(Camera* camera, const HexagonMaterial&& hexagonMaterial) {
	camera_ = camera;
	hexagon_ = hexagonMaterial;
}

//更新
void Hexagon::Update() {
	//法線ベクトルの作成
	CreateNormal();
	for (int i = 0; i < kVertexNum; i++) {
		float theta = 60.0f * static_cast<float>(i);
		float angle = theta * rad;
		//正面
		localVertex[0][i].x = hexagon_.size.x * std::cosf(angle);
		localVertex[0][i].y = hexagon_.size.y;
		localVertex[0][i].z = hexagon_.size.z * std::sinf(angle);
		//背面
		localVertex[1][i].x = hexagon_.size.x * std::cosf(angle);
		localVertex[1][i].y = -hexagon_.size.y;
		localVertex[1][i].z = hexagon_.size.z * std::sinf(angle);
	}

	for (int i = 0; i < Surface; i++) {
		for (int j = 0; j < 6; j++) {
			screenVertex[i][j] = ScreenTransform(camera_, localVertex[i][j], rotate_, hexagon_.center);
		}
	}
}

//デバックテキスト
void Hexagon::DebugText(const char* name) {
	std::string centerText = static_cast<std::string>(name) + ".center";
	ImGui::DragFloat3(centerText.c_str(), &hexagon_.center.x, 0.1f);
	std::string radiusText = static_cast<std::string>(name) + ".size";
	ImGui::SliderFloat3(radiusText.c_str(), &hexagon_.size.x, 0.0f, 2.0f);
	std::string rotateText = static_cast<std::string>(name) + ".rotate";
	ImGui::DragFloat3(rotateText.c_str(), &rotate_.x, 0.1f);
}

//描画
void Hexagon::Draw() {
	for (int i = 0; i < Surface; i++) {
		for (int j = 1; j < kVertexNum; j++) {
			Novice::DrawLine((int)screenVertex[i][j - 1].x, (int)screenVertex[i][j - 1].y, (int)screenVertex[i][j].x, (int)screenVertex[i][j].y, hexagon_.color);
			Novice::DrawLine((int)screenVertex[0][j].x, (int)screenVertex[0][j].y, (int)screenVertex[1][j].x, (int)screenVertex[1][j].y, hexagon_.color);
		}
		Novice::DrawLine((int)screenVertex[i][5].x, (int)screenVertex[i][5].y, (int)screenVertex[i][0].x, (int)screenVertex[i][0].y, hexagon_.color);
	}
	Novice::DrawLine((int)screenVertex[0][0].x, (int)screenVertex[0][0].y, (int)screenVertex[1][0].x, (int)screenVertex[1][0].y, hexagon_.color);

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

//頂点のゲッター(local)
Vector3* Hexagon::GetLocalVertex(int i) {
	return localVertex[i];
}

//頂点のゲッター(screen)
Vector3* Hexagon::GetScreenVertex(int i){
	return screenVertex[i];
}

// 六角形の素材のゲッター
GameObject::HexagonMaterial Hexagon::GetHexagonMaterial() {
	return hexagon_;
}

//回転のゲッター
Vector3 Hexagon::GetRotate() {
	return rotate_;
}

//法線ベクトルを作成
void Hexagon::CreateNormal() {
	//面の法線を算出
	Vector3 v01 = GetLocalVertex(0)[1] - GetLocalVertex(0)[0];
	Vector3 v111 = GetLocalVertex(0)[1] - GetLocalVertex(1)[1];

	Vector3 v12 = GetLocalVertex(0)[2] - GetLocalVertex(0)[1];
	Vector3 v112 = GetLocalVertex(0)[2] - GetLocalVertex(1)[2];

	Vector3 v23 = GetLocalVertex(0)[3] - GetLocalVertex(0)[2];
	Vector3 v113 = GetLocalVertex(0)[3] - GetLocalVertex(1)[3];

	//面の法線
	hexagon_.normal[0] = Math::Normalize(Math::Cross(v01, v111));
	hexagon_.normal[1] = Math::Normalize(Math::Cross(v12, v112));
	hexagon_.normal[2] = Math::Normalize(Math::Cross(v23, v113));
	hexagon_.normal[3] = Math::Normalize(Math::Cross(v01, v12));
}