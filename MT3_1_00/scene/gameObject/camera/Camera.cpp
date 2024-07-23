#include "Camera.h"
#include "Vector2.h"

//初期化
void Camera::Initialize(int kWindowWidth, int kWindowHeight) {
	windowWidth_ = kWindowWidth; //横幅
	windowHeight_ = kWindowHeight;//縦幅
	//カメラ
	scale_ = { 1.0f,1.0f,1.0f };     //倍率
	rotate_ = { 0.26f,0.0f,0.0f };
	translate_ = { 0.0f,0.0f,-10.0f };//ポジション
	preMousePos_ = mousePos_;
}

//更新処理
void Camera::Update(char* keys, char* preKeys) {
	bool left = keys[DIK_LEFT] && preKeys[DIK_LEFT];
	bool right = keys[DIK_RIGHT] && preKeys[DIK_RIGHT];
	bool up = keys[DIK_UP] && preKeys[DIK_UP] && !keys[DIK_LSHIFT] && !preKeys[DIK_LSHIFT];
	bool down = keys[DIK_DOWN] && preKeys[DIK_DOWN] && !keys[DIK_LSHIFT] && !preKeys[DIK_LSHIFT];
	bool front = keys[DIK_UP] && preKeys[DIK_UP] && keys[DIK_LSHIFT] && preKeys[DIK_LSHIFT];
	bool behide = keys[DIK_DOWN] && preKeys[DIK_DOWN] && keys[DIK_LSHIFT] && preKeys[DIK_LSHIFT];

	GameObject::Movement(left, right, up, down, front, behide, -1.0f);

#ifdef _DEBUG
	//拡大縮小
	GameObject::Scaling();

	//回転
	GameObject::Rotation();
#endif // _DEBUG

	RenderingPipeline();
}

#ifdef _DEBUG
//デバックテキスト
void Camera::DebugText() {
	ImGui::DragFloat3("CamereRotate", &rotate_.x, 0.01f);
	ImGui::DragFloat3("CameraTranslate", &translate_.x, 0.01f);
}
#endif // _DEBUG

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
 Matrix4x4 Camera::GetProjctionMatrix()const {
	// TODO: return ステートメントをここに挿入します
	return projectionMatrix_;
}

 //ビューマトリックスのゲッター
 Matrix4x4 Camera::GetViewMatrix() const
 {
	 return viewMatrix_;
 }

//レンダリングパイプライン
void Camera::RenderingPipeline() {
	//カメラ座標系
	cameraMatrix_ = Math::MakeSTRMatrix(scale_, rotate_, translate_);
	//ビュー座標系
	viewMatrix_ = ~cameraMatrix_;
	//同次クリップ座標系
	projectionMatrix_ = Math::MakePerspectiveFovMatrix(0.45f, float(windowWidth_) / float(windowHeight_), 0.1f, 100.0f);
	//ビュープロジェクションマトリックス
	viewProjectionMatrix_ = viewMatrix_ * projectionMatrix_;
	//ビューポートマトリックス
	viewportMatrix_ = Math::MakeViewportMatrix(0, 0, float(windowWidth_), float(windowHeight_), 0.0f, 1.0f);
}
