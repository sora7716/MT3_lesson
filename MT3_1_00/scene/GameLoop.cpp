#include "GameLoop.h"
#include"Imgui.h"

//コンストラクター
GameLoop::GameLoop() {
	for (int i = 0; i < kKeysNums; i++) {
		keys_[i] = { 0 };
		preKeys_[i] = { 0 };
	}
	camera_ = nullptr;
	triangle_ = nullptr;
	grid_ = nullptr;
	for (int i = 0; i < kSphereNum; i++) {
		sphere_[i] = nullptr;
	}
	line_ = nullptr;
	point1_ = nullptr;
	point2_ = nullptr;
	plane_ = nullptr;
}

//デストラクター
GameLoop::~GameLoop() {
	delete camera_;
	delete plane_;
	delete* sphere_;
	delete triangle_;
	delete grid_;
	delete line_;
	delete point1_;
	delete point2_;
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
void GameLoop::Create() {
	camera_ = new Camera();
	grid_ = new Grid();
	for (int i = 0; i < kSphereNum; i++) {
		sphere_[i] = new Sphere();
	}
	triangle_ = new Triangle();
	plane_ = new Plane();
	line_ = new Point();
	point1_ = new Sphere();
	point2_ = new Sphere();
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Create();//生成
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	camera_->Initialize(kWindowWidth, kWindowHeight);
	line_->Initialize(camera_);
	line_->SetSegment({ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} });
	line_->SetPoint({ -1.5f,0.6f,0.6f });
	grid_->Initialize(camera_);

	for (int i = 0; i < kSphereNum; i++) {
		sphere_[i]->Initialize(camera_);
		sphere_[i]->SetSphere({ 0.0f + (float)i,0.0f + (float)i,0.0f + (float)i,{1.0f},WHITE });
	}

	triangle_->Initialize(kWindowWidth, kWindowHeight,camera_);
	plane_->Initialize(camera_);
	plane_->SetPlane({ {0.0f,1.0f,0.0f},1.0f,RED });
}

//更新処理
void GameLoop::Update() {
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
	DebugText();//デバックテキスト

	camera_->Update(keys_, preKeys_);
	for (int i = 0; i < kSphereNum; i++) {
		sphere_[i]->Update();
	}
	grid_->Update(keys_, preKeys_);
	//sphere_[0]->IsCollision(sphere_[1]->GetSphereMaterial(),sphere_[1]->GetWorldPosition());
	//sphere_[1]->IsCollision(sphere_[0]->GetSphereMaterial());
	point1_->Initialize(camera_);
	point1_->SetSphere({ line_->GetPoint(), 0.01f,RED });
	point2_->Initialize(camera_);
	point2_->SetSphere({ line_->GetClosestPoint(), 0.01f,BLACK });
	line_->Update();
	sphere_[0]->IsCollision(plane_);
	triangle_->Update(keys_, preKeys_);//三角形
}

//デバックテキスト
void GameLoop::DebugText() {
	ImGui::Begin("window");
	camera_->DebugText();
	sphere_[0]->DebugText("sphere.center", "sphere.radius", "sphere.rotate");
	//sphere_[1]->DebugText("sphere[1].center", "sphere[1].radius","sphere[1].rotate");
	/*for (int i = 0; i < Grid::kElementCount; i++) {
		grid_->DebugText(i);
	}*/
	//line_->DebugText();
	plane_->DebugText();
	ImGui::End();
}

//描画処理
void GameLoop::Draw() {
	grid_->Draw();
	for (int i = 0; i < kSphereNum; i++) {
		sphere_[i]->Draw();
	}
	plane_->Draw();
	/*line_->Draw();
	point1_->Draw();
	point2_->Draw();*/
	//triangle_->Draw();
}