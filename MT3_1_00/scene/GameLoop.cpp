﻿#include "GameLoop.h"
#include"Imgui.h"

//コンストラクター
GameLoop::GameLoop(){
}

//デストラクター
GameLoop::~GameLoop(){
	delete triangle_;
	delete camera_;
	delete grid_;
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	camera_ = new Camera();
	triangle_ = new Triangle();
	grid_ = new Grid();
	grid_->Initialize(camera_);
	triangle_->Initialize(kWindowWidth, kWindowHeight,camera_);
}

//更新処理
void GameLoop::Update(){
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
	camera_->Update(keys_,preKeys_);
	triangle_->Update(keys_,preKeys_);
	ImGui::Begin("window");
	ImGui::DragFloat3("cameraTranslate", &camera_->translate_.vector.x, 0.01f);
	ImGui::End();
}

//描画処理
void GameLoop::Draw(){
	triangle_->Draw();
	grid_->Draw();
}

//ゲームループ
void GameLoop::Loop(){

	Initialize();//初期化処理

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		
		Update();//更新処理

		Draw();  //描画処理

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys_[DIK_ESCAPE] == 0 && keys_[DIK_ESCAPE] != 0) {
			break;
		}
	}

}
