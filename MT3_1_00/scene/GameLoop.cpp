#include "GameLoop.h"
#include"Imgui.h"

//コンストラクター
GameLoop::GameLoop(){
}

//デストラクター
GameLoop::~GameLoop(){
	delete triangle_;
	delete camera_;
	delete grid_;
	delete shpere_;
}

//ゲームループ
void GameLoop::Loop() {

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


//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	camera_ = new Camera();
	triangle_ = new Triangle();
	grid_ = new Grid();
	grid_->Initialize(camera_);
	triangle_->Initialize(kWindowWidth, kWindowHeight,camera_);
	shpere_ = new Sphere();
	shpere_->Initialize(camera_);

}

//更新処理
void GameLoop::Update(){
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
	DebugText();//デバックテキスト

	//triangle_->Update(keys_,preKeys_);
	camera_->Update(keys_,preKeys_);
	shpere_->Update();
	
}

//描画処理
void GameLoop::Draw(){
	triangle_->Draw();
	grid_->Draw();
	shpere_->Draw();
}

//デバックテキスト
void GameLoop::DebugText(){
	ImGui::Begin("window");
	camera_->DebugText();
	shpere_->DebugText();
	ImGui::End();
}
