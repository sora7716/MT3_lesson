#include "GameLoop.h"

#ifdef _DEBUG
#include"Imgui.h"
#endif // _DEBUG


//コンストラクター
GameLoop::GameLoop() {

}

//デストラクター
GameLoop::~GameLoop() {
	delete camera_;
	delete plane_;
	delete* spheres_;
	delete triangle_;
	delete grid_;
	delete line_;
	delete point1_;
	delete point2_;
	delete collision_;
	delete* aabbs_;
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
		spheres_[i] = new Sphere();
	}
	triangle_ = new Triangle();
	plane_ = new Plane();
	line_ = new Line();
	point1_ = new Sphere();
	point2_ = new Sphere();
	collision_ = new Collision();
	
	for (int i = 0; i < kAABBNum; i++) {
		aabbs_[i] = new AABB();
	}
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Create();//生成
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	camera_->Initialize(kWindowWidth, kWindowHeight);
	line_->Initialize(camera_);
	line_->SetPoint({ -1.5f,0.6f,0.6f });
	line_->SetSegment({ {0.0f,1.0f,-0.5f},{0.0f,0.0f,1.0f} });
	grid_->Initialize(camera_);
	for (int i = 0; i < kSphereNum; i++) {
		spheres_[i]->Initialize(camera_);
		spheres_[i]->SetSphere({ 0.0f + (float)i,0.0f + (float)i,0.0f + (float)i,{1.0f},WHITE });
	}
	triangle_->Initialize(kWindowWidth, kWindowHeight, camera_);
	plane_->Initialize(camera_);
	plane_->SetPlane({ {0.0f,1.0f,0.0f},1.0f,RED });
	point1_->Initialize(camera_);
	point2_->Initialize(camera_);

	aabbs_[0]->Initialize(camera_, { { -0.5f,-0.5f,-0.5f },{},WHITE,false});
	//aabbs_[1]->Initialize(camera_, { { 0.2f,0.2f,0.2f },{1.0f,1.0f,1.0f},WHITE,false});
}

//更新処理
void GameLoop::Update() {
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
	DebugText();//デバックテキスト

	camera_->Update(keys_, preKeys_);
	for (Sphere* sphere : spheres_) {
		sphere->Update();
	}
	grid_->Update();
	point1_->SetSphere({ line_->GetPoint(), 0.01f,RED });
	point2_->SetSphere({ line_->GetClosestPoint(), 0.01f,BLACK });
	line_->Update();
	triangle_->Update(keys_, preKeys_);//三角形

	for (AABB* aabb : aabbs_) {
		aabb->Update();
	}
}

#ifdef _DEBUG
//デバックテキスト
void GameLoop::DebugText() {
	ImGui::Begin("window");
	/*line_->DebugText();
	triangle_->DebugText();*/
	//plane_->DebugText();
	spheres_[0]->DebugText("sphere[0]");
	//spheres_[1]->DebugText("sphere[1]");
	//camera_->DebugText();
	/*for (int i = 0; i < Grid::kElementCount; i++) {
		grid_->DebugText(i);
	}*/
	aabbs_[0]->DebugText("aabb1");
	//aabbs_[1]->DebugText("aabb2");
	ImGui::End();
}
#endif // _DEBUG

//当たり判定
void GameLoop::Collider() {
	//collision_->IsCollision(sphere_[0], sphere_[0]->GetSphereMaterial(), sphere_[1]->GetSphereMaterial());
	//collision_->IsCollision(sphere_[0], sphere_[0]->GetSphereMaterial(),plane_->GetPlaneMaterial());
	//collision_->IsCollision(line_, line_->GetSegment(), plane_->GetPlaneMaterial());
	//collision_->IsCollision(line_,line_->GetSegment(),triangle_->GetTriangleMaterial());
	//collision_->IsCollision(aabbs_[0], aabbs_[0]->GetAABBMaterial(), aabbs_[1]->GetAABBMaterial());
	collision_->IsCollision(aabbs_[0], aabbs_[0]->GetAABBMaterial(), spheres_[0]->GetSphereMaterial());
}

//描画処理
void GameLoop::Draw() {
	grid_->Draw();
	for (AABB* aabb : aabbs_) {
		aabb->Draw();
	}
	//line_->Draw();
	//plane_->Draw();
	for (Sphere*sphere: spheres_) {
		sphere->Draw();
	}
	/*point1_->Draw();
	point2_->Draw();*/
	//triangle_->WireFrameDraw();
	Collider();
}