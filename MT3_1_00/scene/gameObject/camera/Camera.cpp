#include "Camera.h"

//初期化
void Camera::Initialize(int kWindowWidth, int kWindowHeight){
	windowWidth_  = kWindowWidth; //横幅
	windowHeight_ = kWindowHeight;//縦幅
	//カメラ
	scale_.SetVector({ 1.0f,1.0f,1.0f });     //倍率
	translate_.SetVector({ 0.0f,0.0f,-5.0f });//ポジション
}

//更新処理
void Camera::Update(char *keys,char *preKeys){
	GameObject::Translate(keys[DIK_LEFT], preKeys[DIK_LEFT], keys[DIK_RIGHT], preKeys[DIK_RIGHT],-1.0f);
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
