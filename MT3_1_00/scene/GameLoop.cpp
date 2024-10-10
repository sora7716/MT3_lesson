#include "GameLoop.h"
using namespace std;
#ifdef _DEBUG
#include"Imgui.h"
#endif // _DEBUG

#pragma region 基本いじらないやつ
//コンストラクター
GameLoop::GameLoop() {
}

//デストラクター
GameLoop::~GameLoop() {
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

#pragma endregion 基本いじらないやつ

//生成
void GameLoop::Create() {
	//カメラ
	camera_ = make_unique<Camera>();
	//グリッド線
	grid_ = make_unique<Grid>();
	//ライン
	line_ = make_unique<Line>();
	//六角形
	hexagon_ = make_unique<Hexagon>();
	//OBB
	obb_ = make_unique<OBB>();
	//当たり判定
	collision_ = make_unique<Collision>();
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Create();//生成
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	//カメラ
	camera_->Initialize(kWindowWidth, kWindowHeight);
	//グリッド線
	grid_->Initialize(camera_.get());
	//ライン
	segment_ = {
		{1.0f,1.0f,1.0f},
		{0.5f,0.5f,0.5f}
	};
	line_->Initialize(camera_.get(), move(segment_));
	//六角形
	hexagonMaterial_ = { {},1};
	hexagon_->Initialize(camera_.get(), move(hexagonMaterial_));
	//OBB
	obbMaterial_ = {
		.center = {5,0.0f,5.0f},
	};
	obb_->Initialize(camera_.get(), move(obbMaterial_));
}

//更新処理
void GameLoop::Update() {
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
#ifdef _DEBUG
	DebugText();//デバックテキスト
#endif // _DEBUG
	//衝突判定
	Collider();

	//カメラ
	camera_->Update(keys_,preKeys_);
	//グリッド線
	grid_->Update();
	//ライン
	line_->Update();
	//六角形
	hexagon_->Update();
	//OBB
	obb_->Update();
}

#ifdef _DEBUG
//デバックテキスト
void GameLoop::DebugText() {
	ImGui::Begin("Window");
	camera_->DebugText();
	line_->DebugText();
	hexagon_->DebugText();
	obb_->DebagText();
	ImGui::End();
}
#endif // _DEBUG

//当たり判定
void GameLoop::Collider() {

}

//描画処理
void GameLoop::Draw() {
	//グリッド線
	grid_->Draw();
	//ライン
	line_->DrawSegment();
	//六角形
	hexagon_->Draw();
	//OBB
	obb_->Draw();
}