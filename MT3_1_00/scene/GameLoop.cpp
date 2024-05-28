#include "GameLoop.h"

//コンストラクター
GameLoop::GameLoop(){
}

//デストラクター
GameLoop::~GameLoop(){
	delete triangle_;
	delete camera_;
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	camera_ = new Camera();
	triangle_ = new Triangle();
	triangle_->Initialize(kWindowWidth, kWindowHeight,camera_);
}

//更新処理
void GameLoop::Update(){
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
	camera_->Update(keys_,preKeys_);
	triangle_->Update(keys_,preKeys_);
}

//描画処理
void GameLoop::Draw(){
	triangle_->Draw();
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
