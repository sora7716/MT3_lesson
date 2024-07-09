#include "Camera.h"

//初期化
void Camera::Initialize(int kWindowWidth, int kWindowHeight) {
	windowWidth_ = kWindowWidth; //横幅
	windowHeight_ = kWindowHeight;//縦幅
	//カメラ
	scale_ = { 1.0f,1.0f,1.0f };     //倍率
	rotate_ = { 0.26f,0.0f,0.0f };
	translate_ = { 0.0f,0.0f,-5.0f };//ポジション
}

//更新処理
void Camera::Update(char* keys, char* preKeys) {
	bool left = keys[DIK_LEFT] && preKeys[DIK_LEFT];
	bool right = keys[DIK_RIGHT] && preKeys[DIK_RIGHT];
	bool up = keys[DIK_UP] && preKeys[DIK_UP] && !keys[DIK_LSHIFT] && !preKeys[DIK_LSHIFT];
	bool down = keys[DIK_DOWN] && preKeys[DIK_DOWN] && !keys[DIK_LSHIFT] && !preKeys[DIK_LSHIFT];
	bool front = keys[DIK_UP] && preKeys[DIK_UP] && keys[DIK_LSHIFT] && preKeys[DIK_LSHIFT];
	bool behide = keys[DIK_DOWN] && preKeys[DIK_DOWN] && keys[DIK_LSHIFT] && preKeys[DIK_LSHIFT];

	bool press_D = keys[DIK_D] && preKeys[DIK_D];
	bool press_A = keys[DIK_A] && preKeys[DIK_A];
	bool press_W = keys[DIK_W] && preKeys[DIK_W];
	bool press_S = keys[DIK_S] && preKeys[DIK_S];
	bool press_E = keys[DIK_E] && preKeys[DIK_E];
	bool press_Q = keys[DIK_Q] && preKeys[DIK_Q];
	GameObject::Movement(left, right, up, down, front, behide, -1.0f);
	GameObject::Rotation(press_D, press_A, press_W, press_S, press_E, press_Q);
	RenderingPipeline();
}

//デバックテキスト
void Camera::DebugText() {
	ImGui::DragFloat3("CamereRotate", &rotate_.x, 0.01f);
	ImGui::DragFloat3("CameraTranslate", &translate_.x, 0.01f);
}

//レンダリングパイプライン
void Camera::RenderingPipeline() {
	//カメラ座標系
	cameraMatrix_ = Math::STRMatrix(scale_, rotate_, translate_);
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
void Camera::Draw() {
}

// ビュープロジェクションマトリックスのゲッター
Matrix4x4 Camera::GetViewProjectionMatrix()const {
	return viewProjectionMatrix_;
}

//ビューポートマトリックスのゲッター
Matrix4x4 Camera::GetViewportMatrix()const {
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
Vector3 Camera::GetTranslate() {
	return translate_;
}

//同次クリップ空間のゲッター
const Matrix4x4& Camera::GetProjctionMatrix() {
	// TODO: return ステートメントをここに挿入します
	return projectionMatrix_;
}
;
