#include "Triangle.h"
#include <string>
using namespace std;

//初期化
void Triangle::Initialize(Camera* camera, int kWindowWidth, int kWindowHeight, const TriangleMaterial&& triangleMaterial) {
	camera_ = camera;//カメラ
	windowHeight_ = kWindowHeight;//縦幅
	windowWidth_ = kWindowWidth;//横幅
	camera_->Initialize(windowWidth_, windowHeight_);//カメラの初期化
	v1_ = { 1.2f,-3.9f,2.5f };//ベクトル1
	v2_ = { 2.8f,0.4f,-1.3f };//ベクトル2

	//三角ポリゴン
	scale_ = { 1.0f,1.0f,1.0f };        //倍率
	translate_ = { 0.0f,1.0f,0.0f };        //ポジション
	radian_.y = 5.0f / 60.0f;

	triangle_ = triangleMaterial;
}

//更新
void Triangle::Update(char* keys, char* preKeys) {
	cross_ = Math::Cross(v1_, v2_);//クロス積の計算

	camera_->Update(keys, preKeys);//カメラの更新処理
	for (uint32_t i = 0; i < 3; i++) {
		CameraScreenTransform(camera_, triangle_.kLocalVertices_[i], screenVertices_[i]);
	}
	//Transfar(keys, preKeys);//三角形の動き
}

#ifdef _DEBUG
//デバックテキスト
void Triangle::DebugText(const char* name) {
	string topLabel = (string)name + ".vertex.top";
	ImGui::DragFloat2(topLabel.c_str(), &triangle_.kLocalVertices_[(int)Vertex::kTop].x, 0.01f);
	string rightLabel = (string)name + ".vertex.right";
	ImGui::DragFloat2(rightLabel.c_str(), &triangle_.kLocalVertices_[(int)Vertex::kRight].x, 0.01f);
	string leftLabel = (string)name + ".vertex.left";
	ImGui::DragFloat2(leftLabel.c_str(), &triangle_.kLocalVertices_[(int)Vertex::kLeft].x, 0.01f);
}
#endif // _DEBUG

//描画
void Triangle::Draw()const {
	//クロス積
	//ScreenPrintf::VectorScreenPrintf(0, 0, cross_, "Cross");
	//三角ポリゴン
	Novice::DrawTriangle(
		int(screenVertices_[(int)Vertex::kTop].x), int(screenVertices_[(int)Vertex::kTop].y),
		int(screenVertices_[(int)Vertex::kRight].x), int(screenVertices_[(int)Vertex::kRight].y),
		int(screenVertices_[(int)Vertex::kLeft].x), int(screenVertices_[(int)Vertex::kLeft].y),
		RED, kFillModeSolid);
}

//ワイヤーフレームで描画
void Triangle::DrawWireFrame()const {
	//三角ポリゴン
	Novice::DrawTriangle(
		int(screenVertices_[(int)Vertex::kTop].x), int(screenVertices_[(int)Vertex::kTop].y),
		int(screenVertices_[(int)Vertex::kRight].x), int(screenVertices_[(int)Vertex::kRight].y),
		int(screenVertices_[(int)Vertex::kLeft].x), int(screenVertices_[(int)Vertex::kLeft].y),
		triangle_.color, kFillModeWireFrame);
}

//衝突時の判定
void Triangle::OnCollisiton(bool isHit) {
	triangle_.isHit = isHit;
	if (triangle_.isHit) {
		SetColor(RED);
	}
	else {
		SetColor(WHITE);
	}
}

//三角形のマテリアルのゲッター
Triangle::TriangleMaterial Triangle::GetTriangleMaterial() const {
	return triangle_;
}

//カラーのセッター
void Triangle::SetColor(uint32_t color) {
	triangle_.color = color;
}

//動き
void Triangle::Transfar(char* keys, char* preKeys) {
	bool left = keys[DIK_A] && preKeys[DIK_A];
	bool right = keys[DIK_D] && preKeys[DIK_D];
	bool front = keys[DIK_S] && preKeys[DIK_S];
	bool behind = keys[DIK_W] && preKeys[DIK_W];
	GameObject::Scale(behind, front);//拡縮
	GameObject::Rotate();//回転
	GameObject::TranslateX(left, right, 1.0f);//移動
}
