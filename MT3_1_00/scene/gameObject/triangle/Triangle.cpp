#include "Triangle.h"

enum {
	left,
	top,
	right,
};

void Triangle::Initialize(int kWindowWidth,int kWindowHeight,Camera* camera) {
	camera_       = camera;//カメラ
	windowHeight_ = kWindowHeight;//縦幅
	windowWidth_  = kWindowWidth;//横幅
	camera_->Initialize(windowWidth_, windowHeight_);//カメラの初期化
	v1_.SetVector({ 1.2f,-3.9f,2.5f });//ベクトル1
	v2_.SetVector({ 2.8f,0.4f,-1.3f });//ベクトル2

	//三角ポリゴン
	scale_.SetVector     ({ 1.0f,1.0f,1.0f });        //倍率
	translate_.SetVector ({ 0.0f,0.5f,5.0f });        //ポジション
	radian_.y = 5.0f / 60.0f;

	//ローカル座標
	kLocalVertices_[left].SetVector ({ -1.0f, -1.0f, 0.0f });
	kLocalVertices_[top].SetVector  ({ 0.0f,  1.0f, 0.0f  });
	kLocalVertices_[right].SetVector({ 1.0f, -1.0f, 0.0f  });
}

void Triangle::Update(char *keys, char *preKeys) {
	cross_ = Math::Cross(v1_, v2_);//クロス積の計算
	Scale(keys, preKeys);//拡縮
	Rotation();//回転
	Transfer(keys,preKeys);//移動
	camera_->Update(keys,preKeys);//カメラの更新処理
	RenderingPipeline();//レンダリングパイプライン
}

//拡大
void Triangle::Scale(char* keys, char* preKeys){
	scale_ += velocity_;//拡縮
	//キー入力
	if (keys[DIK_W] && preKeys[DIK_W] && scale_.GetVector().x < 2.0f) {
		velocity_.z = 5.0f / 60.0f;
	}
	else if (keys[DIK_S] && preKeys[DIK_S] && scale_.GetVector().x > 0.5f) {
		velocity_.z = -5.0f / 60.0f;
	}
	else { velocity_.z = 0.0f; }
}

//回転
void Triangle::Rotation(){
	rotate_ += radian_;//回転
}

//移動
void Triangle::Transfer(char *keys, char *preKeys){
	translate_ += velocity_;//移動
	//キー入力
	if (keys[DIK_A] && preKeys[DIK_A]) {
		velocity_.x = -5.0f / 60.0f;
	}
	else if (keys[DIK_D] && preKeys[DIK_D]) {
		velocity_.x = 5.0f / 60.0f;
	}
	else { velocity_.x = 0.0f; }
}

//レンダリングパイプライン
void Triangle::RenderingPipeline() {
	//ワールド座標系
	worldMatrix_ = Math::MakeAffineMatrix(scale_.GetVector(), rotate_.GetVector(), translate_.GetVector());
	//wvpマトリックス
	worldViewProjectionMatrix = worldMatrix_ * camera_->GetViewProjectionMatrix();
	for (uint32_t i = 0; i < 3; ++i) {
		//正規化デバイス座標系
		ndcVertex = Math::Transform(kLocalVertices_[i], worldViewProjectionMatrix);
		//スクリーン座標
		screenVertices_[i] = Math::Transform(ndcVertex, camera_->GetViewportMatrix());
	}
}

void Triangle::Draw() {
	//クロス積
	ScreenPrintf::VectorScreenPrintf(0, 0, cross_, "Cross");
	//三角ポリゴン
	Novice::DrawTriangle(
		int(screenVertices_[left] .GetVector().x ), int(screenVertices_[left] .GetVector().y ),
		int(screenVertices_[top]  .GetVector().x ), int(screenVertices_[top]  .GetVector().y ),
		int(screenVertices_[right].GetVector().x ), int(screenVertices_[right].GetVector().y ),
		RED, kFillModeSolid);
}