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

	camera_->Update(keys,preKeys);//カメラの更新処理
	ScreenTransform(camera_, worldMatrix_,worldViewProjectionMatrix_,kLocalVertices_,ndcVertex_,screenVertices_,3);
	bool left = keys[DIK_A] && preKeys[DIK_A];
	bool right = keys[DIK_D] && preKeys[DIK_D];
	bool front = keys[DIK_S]&&preKeys[DIK_S];
	bool behind = keys[DIK_W]&&preKeys[DIK_W];
	GameObject::Scale(behind,front);//拡縮
	GameObject::Rotate();//回転
	GameObject::Translate(left, right,1.0f);//移動
}

void Triangle::Draw() {
	//クロス積
	//ScreenPrintf::VectorScreenPrintf(0, 0, cross_, "Cross");
	//三角ポリゴン
	Novice::DrawTriangle(
		int(screenVertices_[left].GetVector().x),  int(screenVertices_[left].GetVector().y ),
		int(screenVertices_[top].GetVector().x),   int(screenVertices_[top].GetVector().y  ),
		int(screenVertices_[right].GetVector().x), int(screenVertices_[right].GetVector().y),
		RED, kFillModeSolid);
}