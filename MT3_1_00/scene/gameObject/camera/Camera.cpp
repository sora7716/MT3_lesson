#include "Camera.h"

//初期化
void Camera::Initialize(int kWindowWidth, int kWindowHeight){
	windowWidth_  = kWindowWidth; //横幅
	windowHeight_ = kWindowHeight;//縦幅
	//カメラ
	scale_.SetVector({ 1.0f,1.0f,1.0f });     //倍率
	rotate_.SetVector({0.26f,0.0f,0.0f});
	translate_.SetVector({ 0.0f,1.9f,-6.49f });//ポジション
}

//更新処理
void Camera::Update(char *keys,char *preKeys){
	bool left = keys[DIK_LEFT] && preKeys[DIK_LEFT];
	bool right = keys[DIK_RIGHT]&&preKeys[DIK_RIGHT];
	GameObject::Translate(left, right,-1.0f);
	RenderingPipeline();
}

//レンダリングパイプライン
void Camera::RenderingPipeline(){
	//カメラ座標系
	cameraMatrix_ = Math::MakeAffineMatrix(scale_.GetVector(), rotate_.GetVector(), translate_.GetVector());
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
