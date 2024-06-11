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
	v1_ = { 1.2f,-3.9f,2.5f };//ベクトル1
	v2_ = { 2.8f,0.4f,-1.3f };//ベクトル2

	//三角ポリゴン
	scale_    = { 1.0f,1.0f,1.0f };        //倍率
	translate_= { 0.0f,0.5f,5.0f };        //ポジション
	radian_.y = 5.0f / 60.0f;

	//ローカル座標
	kLocalVertices_[left]  = { -1.0f, -1.0f, 0.0f };
	kLocalVertices_[top]   = { 0.0f,  1.0f, 0.0f  };
	kLocalVertices_[right] = { 1.0f, -1.0f, 0.0f  };
}

void Triangle::Update(char *keys, char *preKeys) {
	cross_ = Math::Cross(v1_, v2_);//クロス積の計算

	camera_->Update(keys,preKeys);//カメラの更新処理
	ScreenTransform(camera_, kLocalVertices_,screenVertices_,3);
	Transfar(keys, preKeys);//三角形の動き
}

void Triangle::Draw() {
	//クロス積
	//ScreenPrintf::VectorScreenPrintf(0, 0, cross_, "Cross");
	//三角ポリゴン
	Novice::DrawTriangle(
		int(screenVertices_[left].x),  int(screenVertices_[left]. y ),
		int(screenVertices_[top].x),   int(screenVertices_[top].y),
		int(screenVertices_[right].x), int(screenVertices_[right].y),
		RED, kFillModeSolid);
}

//動き
void Triangle::Transfar(char* keys, char* preKeys){
	bool left = keys[DIK_A] && preKeys[DIK_A];
	bool right = keys[DIK_D] && preKeys[DIK_D];
	bool front = keys[DIK_S] && preKeys[DIK_S];
	bool behind = keys[DIK_W] && preKeys[DIK_W];
	GameObject::Scale(behind, front);//拡縮
	GameObject::Rotate();//回転
	GameObject::Translate(left, right, 1.0f);//移動
}
