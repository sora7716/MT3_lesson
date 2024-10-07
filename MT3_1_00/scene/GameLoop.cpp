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
	line_ = std::make_unique<Line>();
	for (int i = 0; i < 3; i++) {
		bezierPointSpheres_[i] = std::make_unique<Sphere>();
	}
	point1_ = new Sphere();
	point2_ = new Sphere();
	collision_ = new Collision();

	for (int i = 0; i < kAABBNum; i++) {
		aabbs_[i] = new AABB();
	}
	for (int i = 0; i < kOBBNum; i++) {
		obbs_[i] = std::make_unique<OBB>();
	}

	capsule_ = std::make_unique<Capsule>();

	hexagon_ = std::make_unique<Hexagon>();
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Create();//生成
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	camera_->Initialize(kWindowWidth, kWindowHeight);
	line_->Initialize(camera_, std::move(segment_));
	line_->SetPoint({ -1.5f,0.6f,0.6f });
	line_->SetSegment({ {-0.8f,-0.3f,0.0f},{0.5f,0.5f,0.5f} });
	line_->SetBezierPoints(bezierControlPoints);
	line_->SetColor(BLUE);
	line_->SetCatmullRomPoints(catmullRomPoints_);
	for (int i = 0; i < 3; i++) {
		bezierPointSpheres_[i]->Initialize(camera_);
		bezierPointSpheres_[i]->SetSphere({ line_->GetBezierPoints()[i],0.01f,BLACK,false });
	}
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

	aabbs_[0]->Initialize(camera_, { { -0.5f,-0.5f,-0.5f },{0.5f,0.5f,0.5f},WHITE,false });
	//aabbs_[1]->Initialize(camera_, { { 0.2f,0.2f,0.2f },{1.0f,1.0f,1.0f},WHITE,false});

	obbMaterial_[0] = {
		.center{0.0f,0.0f,0.0f},
		.orientations = {{1.0f,0.0f,0.0f},
						 {0.0f,1.0f,0.0f},
						 {0.0f,0.0f,1.0f}
		},
		.size{0.83f,0.26f,0.24f},
	};
	obbMaterial_[1] = {
		.center{0.9f,0.66f,0.78f},
		.orientations = {{1.0f,0.0f,0.0f},
						 {0.0f,1.0f,0.0f},
						 {0.0f,0.0f,1.0f}
		},
		.size{0.5f,0.37f,0.5f},
		.rotation{-0.05f,-2.49f,0.15f},
	};
	for (int i = 0; i < kOBBNum; i++) {
		obbs_[i]->Initialize(camera_, obbMaterial_[i]);
	}
	capsuleMaterial_ = {
		{-0.8f,-0.3f,0.0f},
		{0.5f,0.5f,0.5f},
		30,
	};
	capsule_->Initialize(camera_, std::move(capsuleMaterial_));
	hexagonMateiral_ = {
		{0.0f,0.0f,0.0f},
		1.0f,
	};
	hexagon_->Initialize(camera_, hexagonMateiral_);
}

//更新処理
void GameLoop::Update() {
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
#ifdef _DEBUG
	DebugText();//デバックテキスト
#endif // _DEBUG


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

	for (auto& obb : obbs_) {
		obb->Update();
	}

	for (int i = 0; i < 3; i++) {
		bezierPointSpheres_[i]->SetSphere({ line_->GetBezierPoints()[i],0.01f,BLACK,false });
	}
	for (int i = 0; i < 4; i++) {
		catmullRomPointSpheres_.resize(4);
		catmullRomPointSpheres_[i] = new Sphere();
		catmullRomPointSpheres_[i]->Initialize(camera_);
		catmullRomPointSpheres_[i]->SetSphere({ line_->GetCatmullRomPoints()[i],0.01f,BLACK,false });
	}

	hexagon_->Update();
}

#ifdef _DEBUG
//デバックテキスト
void GameLoop::DebugText() {
	ImGui::Begin("window");
	line_->DebugText();
	hexagon_->DebugText("hexagon");
	//triangle_->DebugText();
	plane_->DebugText();
	/*spheres_[0]->DebugText("sphere[0]");
	spheres_[1]->DebugText("sphere[1]");*/
	//camera_->DebugText();
	 /*for (int i = 0; i < Grid::kElementCount; i++) {
		 grid_->DebugText(i);
	 }*/
	 //aabbs_[0]->DebugText("aabb1");
	 //aabbs_[1]->DebugText("aabb2");
	 /*obbs_[0]->DebagText("obb1");
	 obbs_[1]->DebagText("obb2");*/
	 /*bezierPointSpheres_[0]->DebugText("controlpoints1");
	 bezierPointSpheres_[1]->DebugText("controlpoints2");
	 bezierPointSpheres_[2]->DebugText("controlpoints3");*/
	ImGui::End();
}
#endif // _DEBUG

//当たり判定
void GameLoop::Collider() {
	//collision_->IsCollision(spheres_[0], spheres_[0]->GetSphereMaterial(), spheres_[1]->GetSphereMaterial());
	//collision_->IsCollision(sphere_[0], sphere_[0]->GetSphereMaterial(),plane_->GetPlaneMaterial());
	//collision_->IsCollision(line_.get(), line_->GetSegment(), plane_->GetPlaneMaterial());
	//collision_->IsCollision(line_,line_->GetSegment(),triangle_->GetTriangleMaterial());
	//collision_->IsCollision(aabbs_[0], aabbs_[0]->GetAABBMaterial(), aabbs_[1]->GetAABBMaterial());
	//collision_->IsCollision(aabbs_[0], aabbs_[0]->GetAABBMaterial(), spheres_[0]->GetSphereMaterial());
	//collision_->IsCollision(aabbs_[0], aabbs_[0]->GetAABBMaterial(), line_->GetSegment());
	//collision_->IsCollision(obb_.get(),spheres_[0]->GetSphereMaterial());
	//collision_->IsCollision(obb_.get(), line_->GetSegment());
	//collision_->IsCollision(obbs_[0].get(), obbs_[1].get());
	hexagon_->OnCollision(collision_->IsCollision(hexagon_.get(), line_.get()));
}

//描画処理
void GameLoop::Draw() {
	grid_->Draw();
	//for (AABB* aabb : aabbs_) {
	//	aabb->Draw();
	//}
	line_->DrawSegment();
	//line_->DrawBezier();
	//line_->DrawCatmullRom();
	/*for (auto& controlPoint : bezierPointSpheres_) {
		controlPoint->Draw();
	}*/
	//for (auto controlPoint : catmullRomPointSpheres_) {
	//	controlPoint->Draw();
	//}
	//plane_->Draw();
	//for (Sphere* sphere : spheres_) {
	//	sphere->Draw();
	//}
	/*point1_->Draw();
	point2_->Draw();*/
	//triangle_->WireFrameDraw();
	/*for (auto& obb : obbs_) {
		obb->Draw();
	}*/

	/*capsule_->Draw();*/

	hexagon_->Draw();
	Collider();
}