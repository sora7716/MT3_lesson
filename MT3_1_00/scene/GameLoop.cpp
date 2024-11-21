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

//生成
void GameLoop::Create(){
	camera_ = new Camera();
	grid_ = new Grid();
	triangle_ = new Triangle();
	shpere_ = new Sphere();
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Create();
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	grid_->Initialize(camera_);
	//triangle_->Initialize(kWindowWidth, kWindowHeight,camera_);
	//shpere_->Initialize(camera_, { 0.0f,0.0f,0.0f,{1.0f}});

}

//更新処理
void GameLoop::Update(){
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
	DebugText();//デバックテキスト

	camera_->Update(keys_,preKeys_);
	//triangle_->Update(keys_,preKeys_);//三角形
	//shpere_->Update();//スフィア
}

//デバックテキスト
void GameLoop::DebugText(){
	ImGui::Begin("window");
	camera_->DebugText();
	//shpere_->DebugText();
	ImGui::End();
}

//描画処理
void GameLoop::Draw() {
	grid_->Draw();
	//triangle_->Draw();
	//shpere_->Draw();
}