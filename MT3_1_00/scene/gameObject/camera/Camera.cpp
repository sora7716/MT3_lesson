#include "Camera.h"

//初期化
void Camera::Initialize(int kWindowWidth, int kWindowHeight){
	windowWidth_  = kWindowWidth; //横幅
	windowHeight_ = kWindowHeight;//縦幅
	//カメラ
	scale_ = { 1.0f,1.0f,1.0f };     //倍率
	rotate_ = {0.26f,0.0f,0.0f};
	translate_ = { 0.0f,2.04f,-5.93f };//ポジション
}

//更新処理
void Camera::Update(char *keys,char *preKeys){
	bool left = keys[DIK_LEFT] && preKeys[DIK_LEFT];
	bool right = keys[DIK_RIGHT]&&preKeys[DIK_RIGHT];
	GameObject::Translate(left, right,-1.0f);
	RenderingPipeline();
}

//デバックテキスト
void Camera::DebugText(){
	ImGui::DragFloat3("CameraTranslate", &translate_.x, 0.01f);
	ImGui::DragFloat3("CamereRotate", &rotate_.x, 0.01f);
	ImGui::DragFloat3("CamereScale", &scale_.x, 0.01f);
}

//レンダリングパイプライン
void Camera::RenderingPipeline(){
	//カメラ座標系
	cameraMatrix_ = Math::MakeAffineMatrix(scale_, rotate_, translate_);
	//ビュー座標系
	viewMatrix_ = ~cameraMatrix_;
	//同次クリップ座標系
	projectionMatrix_ = Math::MakePerspectiveFovMatrix(0.45f, float(windowWidth_) / float(windowHeight_), 0.1f, 100.0f);
	//ビュープロジェクションマトリックス
	viewProjectionMatrix_ = viewMatrix_ * projectionMatrix_;
	//ビューポートマトリックス
	viewportMatrix_ = Math::MakeViewportMatrix(0, 0, float(windowWidth_), float(windowHeight_), 0.0f, 1.0f);
}

//描画
void Camera::Draw(){
}

// ビュープロジェクションマトリックスのゲッター
Matrix4x4 Camera::GetViewProjectionMatrix(){
	return viewProjectionMatrix_;
}

//ビューポートマトリックスのゲッター
Matrix4x4 Camera::GetViewportMatrix(){
	return viewportMatrix_;
}

//スケールのゲッター
Vector3 Camera::GetScale() {
	return scale_;
}

//回転のゲッター
Vector3 Camera::GetRotate() {
	return rotate_;
}

//移動のゲッター
Vector3 Camera::GetTranslate(){
	return translate_;
};
