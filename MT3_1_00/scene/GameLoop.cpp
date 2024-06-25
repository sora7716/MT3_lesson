#include "GameLoop.h"
#include"Imgui.h"

//コンストラクター
GameLoop::GameLoop(){
	for (int i = 0; i < kKeysNums; i++) {
		keys_[i]    = { 0 };
		preKeys_[i] = { 0 };
	}
	camera_   = nullptr;
	triangle_ = nullptr;
	grid_     = nullptr;
	shpere_   = nullptr;
	line_     = nullptr;
	point1_   = nullptr;
	point2_   = nullptr;
	plane_    = nullptr;
}

//デストラクター
GameLoop::~GameLoop(){
	delete camera_;
	delete plane_;
	//delete triangle_;
	//delete grid_;
	//delete shpere_;
	//delete line_;
	//delete point1_;
	//delete point2_;
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
	camera_   = new Camera();
	grid_     = new Grid();
	/*triangle_ = new Triangle();
	shpere_   = new Sphere();
	line_     = new Point();
	point1_   = new Sphere();
	point2_   = new Sphere();*/
	//plane_    = new Plane();
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Create();
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	camera_->Initialize(kWindowWidth, kWindowHeight);
	grid_->Initialize(camera_);
	/*line_->Initialize(camera_);
	line_->SetSegment({ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} });
	line_->SetPoint({ -1.5f,0.6f,0.6f });
	triangle_->Initialize(kWindowWidth, kWindowHeight,camera_);
	shpere_->Initialize(camera_, { 0.0f,0.0f,0.0f,{1.0f}});*/

	plane_->Initialize(camera_,{{0.0f,1.0f,0.0f},1,RED});
}

//更新処理
void GameLoop::Update(){
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
	DebugText();//デバックテキスト

	camera_->Update(keys_, preKeys_);
	//point1_->Initialize(camera_, { line_->GetPoint(), 0.01f,RED });
	//point2_->Initialize(camera_, { line_->GetClosestPoint(), 0.01f,BLACK});
	//line_->Update();
	//triangle_->Update(keys_, preKeys_);//三角形
	//shpere_->Update();//スフィア
}

//デバックテキスト
void GameLoop::DebugText(){
	ImGui::Begin("window");
	camera_->DebugText();
	//line_->DebugText();
	//shpere_->DebugText();
	plane_->DebugText();
	ImGui::End();
}

//描画処理
void GameLoop::Draw() {
	grid_->Draw();
	/*line_->Draw();
	point1_->Draw();
	point2_->Draw();*/
	plane_->Draw();
	//triangle_->Draw();
	//shpere_->Draw(BLACK);
}