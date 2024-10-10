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
	/*for (int i = 0; i < kSphereNum; i++) {
		spheres_[i] = new Sphere();
	}
	triangle_ = new Triangle();*/
	plane_ = new Plane();
	/*line_ = std::make_unique<Line>();
	for (int i = 0; i < 3; i++) {
		bezierPointSpheres_[i] = std::make_unique<Sphere>();
	}
	point1_ = new Sphere();
	point2_ = new Sphere();*/
	collision_ = new Collision();

	/*for (int i = 0; i < kAABBNum; i++) {
		aabbs_[i] = new AABB();
	}
	for (int i = 0; i < kOBBNum; i++) {
		obbs_[i] = std::make_unique<OBB>();
	}*/

	capsule_ = std::make_unique<Capsule>();

	/*hexagon_ = std::make_unique<Hexagon>();*/

	for (int i = 0; i < kBallNum; i++) {
		sphereBall_[i] = std::make_unique<Sphere>();
	}
	//wire_ = std::make_unique<Line>();
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Create();//生成
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	camera_->Initialize(kWindowWidth, kWindowHeight);
	//line_->Initialize(camera_, std::move(segment_));
	//line_->SetPoint({ -1.5f,0.6f,0.6f });
	//line_->SetSegment({ {-0.8f,-0.3f,0.0f},{0.5f,0.5f,0.5f} });
	//line_->SetBezierPoints(bezierControlPoints);
	//line_->SetColor(BLUE);
	//line_->SetCatmullRomPoints(catmullRomPoints_);
	//for (int i = 0; i < 3; i++) {
	//	bezierPointSpheres_[i]->Initialize(camera_);
	//	bezierPointSpheres_[i]->SetSphere({ line_->GetBezierPoints()[i],0.01f,BLACK,false });
	//}
	grid_->Initialize(camera_);
	//for (int i = 0; i < kSphereNum; i++) {
	//	spheres_[i]->Initialize(camera_);
	//	spheres_[i]->SetSphere({ 0.0f + (float)i,0.0f + (float)i,0.0f + (float)i,{1.0f},WHITE });
	//}
	//triangle_->Initialize(kWindowWidth, kWindowHeight, camera_);
	plane_->Initialize(camera_);
	plane_->SetPlane({ {0.0f,1.0f,0.0f},-1.0f,RED });
	/*point1_->Initialize(camera_);
	point2_->Initialize(camera_);*/

	//aabbs_[0]->Initialize(camera_, { { -0.5f,-0.5f,-0.5f },{0.5f,0.5f,0.5f},WHITE,false });
	//aabbs_[1]->Initialize(camera_, { { 0.2f,0.2f,0.2f },{1.0f,1.0f,1.0f},WHITE,false});

	/*obbMaterial_[0] = {
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
	};*/
	/*for (int i = 0; i < kOBBNum; i++) {
		obbs_[i]->Initialize(camera_, obbMaterial_[i]);
	}*/
	capsuleMaterial_ = {
		{{-0.8f,-0.3f,0.0f},
		{0.3f,0.3f,0.3f}},
		0.1f,
	};
	capsule_->Initialize(camera_, std::move(capsuleMaterial_));
	/*hexagonMateiral_ = {
		{0.0f,0.0f,0.0f},
		1.0f,
	};
	hexagon_->Initialize(camera_, hexagonMateiral_);*/

	/*spring_.anchor = { 0.0f,1.0f,0.0f };
	spring_.naturalLength = 0.7f;
	spring_.stiffness = 100.0f;
	spring_.dampingCoefficient = 2.0f;*/

	ball_[0].acceleration = kGravity;
	ball_[0].position = { -0.8f,3.2f,0.3f };
	ball_[0].mass = 1.0f;
	ball_[0].radius = 0.05f;
	ball_[0].color = BLUE;

	ball_[1].acceleration = kGravity;
	ball_[1].position = { -0.8f,3.2f,0.0f };
	ball_[1].mass = 1.0f;
	ball_[1].radius = 0.05f;
	ball_[1].color = RED;
	for (int i = 0; i < kBallNum; i++) {
		sphereBall_[i]->Initialize(camera_);
	}
	/*wireSegment_.origin = spring_.anchor;
	wireSegment_.diff = ball_.position - wireSegment_.origin;
	wire_->Initialize(camera_, std::move(wireSegment_));

	centerPos_ = {};
	centerRadius_ = { 0.8f ,0.8f };

	pendulum_.anchor = { 0.0f,1.0f,0.0f };
	pendulum_.length = 0.8f;
	pendulum_.angle = 0.7f;
	pendulum_.angularVelocity = 0.0f;
	pendulum_.angularaAcceleration = 0.0f;

	conicalPendulum_.anchor = { 0.0f,1.0f,0.0f };
	conicalPendulum_.length = 0.8f;
	conicalPendulum_.halfApexAngle = 0.7f;
	conicalPendulum_.angle = 0.0f;
	conicalPendulum_.angularVelocity = 0.0f;*/
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
	capsule_->Updata();
	//for (Sphere* sphere : spheres_) {
	//	sphere->Update();
	//}
	//grid_->Update();
	//point1_->SetSphere({ line_->GetPoint(), 0.01f,RED });
	//point2_->SetSphere({ line_->GetClosestPoint(), 0.01f,BLACK });
	//line_->Update();
	//triangle_->Update(keys_, preKeys_);//三角形

	//for (AABB* aabb : aabbs_) {
	//	aabb->Update();
	//}

	//for (auto& obb : obbs_) {
	//	obb->Update();
	//}

	//for (int i = 0; i < 3; i++) {
	//	bezierPointSpheres_[i]->SetSphere({ line_->GetBezierPoints()[i],0.01f,BLACK,false });
	//}
	//for (int i = 0; i < 4; i++) {
	//	catmullRomPointSpheres_.resize(4);
	//	catmullRomPointSpheres_[i] = new Sphere();
	//	catmullRomPointSpheres_[i]->Initialize(camera_);
	//	catmullRomPointSpheres_[i]->SetSphere({ line_->GetCatmullRomPoints()[i],0.01f,BLACK,false });
	//}

	//hexagon_->Update();
	//円運動
	//Math::CircularMoveZY(centerPos_, ball_.position, centerRadius_);
	//振り子
	//Math::MakePendulum(pendulum_, ball_.position);
	//フックの法則
	//Math::Hooklaw(spring_,ball_,true);
	//円錐状に動く振り子
	//Math::MakeConicalPendulum(conicalPendulum_, ball_.position);

	static bool isFall = false;
	static bool isMove = false;
	if (ImGui::Button("Fall")) {
		isFall = true;
	}
	if (ImGui::Button("Move")) {
		isMove = true;
	}
	if (isFall) {
		//重力加速
		for (int i = 0; i < kBallNum; i++) {
			ball_[i].velocity += ball_[i].acceleration * deltaTime;
			ball_[i].position += ball_[i].velocity * deltaTime;
			//空気抵抗
			ball_[0].acceleration.y = Math::AirResistance(ball_[0], k).y;
			/*if (ball_[i].position.y < 0.0f) {
				ball_[i].position.y = 0.0f;
				ball_[i].acceleration = {};
				ball_[0].acceleration.x = Math::Friction(ball_[0], miu).x;
			}*/
		}
		if (isMove) {
			ball_[0].velocity.x = 1.0f;
			ball_[1].velocity.x = 1.0f;
			isMove = false;
		}
	}
	//スフィアの素材に代入
	for (int i = 0; i < kBallNum; i++) {
		sphereBallMaterial_[i].center = ball_[i].position;
		sphereBallMaterial_[i].radius = ball_[i].radius;
		sphereBallMaterial_[i].color = ball_[i].color;
		sphereBall_[i]->SetSphere(sphereBallMaterial_[i]);
	}
	//カプセルに代入
	/*capsuleMaterial_.segment.origin = ball_.position;
	capsuleMaterial_.segment.diff = plane_->GetPlaneMaterial().normal * plane_->GetPlaneMaterial().distance;
	capsuleMaterial_.radius = ball_.radius;
	capsule_->SetCapsuleMaterial(capsuleMaterial_);*/
	//線分に代入
	//フックの法則用
	/*wireSegment_.origin = spring_.anchor;
	wireSegment_.diff = ball_.position - wireSegment_.origin;
	wire_->SetSegment(wireSegment_);*/
	//振り子用
	/*wireSegment_.origin = pendulum_.anchor;
	wireSegment_.diff = ball_.position - wireSegment_.origin;
	wire_->SetSegment(wireSegment_);*/
	//円錐の振り子用
	/*wireSegment_.origin = conicalPendulum_.anchor;
	wireSegment_.diff = ball_.position - wireSegment_.origin;
	wire_->SetSegment(wireSegment_);*/

	Collider();
}

#ifdef _DEBUG
//デバックテキスト
void GameLoop::DebugText() {
	ImGui::Begin("window");
	plane_->DebugText();
	capsule_->DebugText("capsule");
	/*line_->DebugText();
	hexagon_->DebugText("hexagon");*/
	//triangle_->DebugText();
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

	/*ImGui::Begin("hook");
	ImGui::DragFloat3("position", &ball_.position.x, 0.01f);
	ImGui::DragFloat3("velocity", &ball_.velocity.x, 0.01f);
	ImGui::DragFloat3("acceleration", &ball_.acceleration.x, 0.01f);
	ImGui::DragFloat("mass", &ball_.mass, 0.1f);
	ImGui::SliderFloat("radius", &ball_.radius, 0.0f, 2.0f);
	ImGui::DragFloat3("anchor", &spring_.anchor.x, 0.1f);
	ImGui::DragFloat("naturalLength", &spring_.naturalLength, 0.1f);
	ImGui::DragFloat("stiffness", &spring_.stiffness, 0.1f);
	ImGui::DragFloat("dampingCoefficient", &spring_.dampingCoefficient, 0.1f);
	ImGui::End();*/

	/*ImGui::Begin("CircularMove");
	ImGui::DragFloat3("position", &ball_.position.x, 0.01f);
	ImGui::DragFloat3("velocity", &ball_.velocity.x, 0.01f);
	ImGui::DragFloat3("acceleration", &ball_.acceleration.x, 0.01f);
	ImGui::DragFloat("mass", &ball_.mass, 0.1f);
	ImGui::SliderFloat("radius", &ball_.radius, 0.0f, 2.0f);
	ImGui::DragFloat3("center", &centerPos_.x, 0.1f);
	ImGui::SliderFloat2("centerRadius", &centerRadius_.x, 0.0f, 2.0f);
	ImGui::End();*/

	//ImGui::Begin("Pendulum");
	//ImGui::DragFloat3("position", &ball_.position.x, 0.01f);
	//ImGui::DragFloat3("velocity", &ball_.velocity.x, 0.01f);
	//ImGui::DragFloat3("acceleration", &ball_.acceleration.x, 0.01f);
	//ImGui::DragFloat("mass", &ball_.mass, 0.1f);
	//ImGui::SliderFloat("radius", &ball_.radius, 0.0f, 2.0f);
	//ImGui::DragFloat3("anchor", &pendulum_.anchor.x, 0.1f);
	//ImGui::SliderFloat("length", &pendulum_.length, -1.0f, 2.0f);
	//ImGui::End();

	/*ImGui::Begin("ConicalPendulum");
	ImGui::DragFloat3("position", &ball_.position.x, 0.01f);
	ImGui::DragFloat3("velocity", &ball_.velocity.x, 0.01f);
	ImGui::DragFloat3("acceleration", &ball_.acceleration.x, 0.01f);
	ImGui::DragFloat("mass", &ball_.mass, 0.1f);
	ImGui::SliderFloat("radius", &ball_.radius, 0.0f, 2.0f);
	ImGui::DragFloat3("anchor", &conicalPendulum_.anchor.x, 0.1f);
	ImGui::SliderFloat("length", &conicalPendulum_.length, 0.1f, 2.0f);
	ImGui::End();*/

	ImGui::Begin("Reflect");
	ImGui::DragFloat3("position", &ball_[0].position.x, 0.01f);
	ImGui::DragFloat3("velocity", &ball_[0].velocity.x, 0.01f);
	ImGui::DragFloat3("acceleration", &ball_[0].acceleration.x, 0.01f);
	ImGui::DragFloat("mass", &ball_[0].mass, 0.1f);
	ImGui::SliderFloat("radius", &ball_[0].radius, 0.0f, 2.0f);
	ImGui::End();

	ImGui::Begin("physics");
	ImGui::DragFloat("miu", &miu, 0.01f);
	ImGui::Text("friction");
	ImGui::DragFloat3("friction.position", &ball_[0].position.x, 0.01f);
	ImGui::DragFloat3("friction.velocity", &ball_[0].velocity.x, 0.01f);
	ImGui::DragFloat3("friction.acceleration", &ball_[0].acceleration.x, 0.01f);
	ImGui::DragFloat("friction.mass", &ball_[0].mass, 0.1f);
	ImGui::SliderFloat("friction.radius", &ball_[0].radius, 0.0f, 2.0f);
	ImGui::Text("normal");
	ImGui::DragFloat3("normal.position", &ball_[1].position.x, 0.01f);
	ImGui::DragFloat3("normal.velocity", &ball_[1].velocity.x, 0.01f);
	ImGui::DragFloat3("normal.acceleration", &ball_[1].acceleration.x, 0.01f);
	ImGui::DragFloat("normal.mass", &ball_[1].mass, 0.1f);
	ImGui::SliderFloat("normal.radius", &ball_[1].radius, 0.0f, 2.0f);
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
	//hexagon_->OnCollision(collision_->IsCollision(hexagon_.get(), line_.get()));
	static float h = 0.1f;
	for (int i = 0; i < kBallNum; i++) {
		/*if (collision_->IsCollision(capsuleMaterial_, plane_->GetPlaneMaterial())) {*/
		if (collision_->IsCollision(sphereBallMaterial_[i], plane_->GetPlaneMaterial())) {
			//反発している
			Math::Reflection(ball_[i].velocity, plane_->GetPlaneMaterial().normal, e);
			ball_[i].position.y += h;//少し上げる
			h *= e;//反発係数を掛ける
		}

		//}
	}
	ImGui::Text("%f", h);
	capsule_->OnCollision(collision_->IsCollision(capsule_.get()->GetCapsuleMaterial(), plane_->GetPlaneMaterial()));
}

//描画処理
void GameLoop::Draw() {
	grid_->Draw();
	//for (AABB* aabb : aabbs_) {
	//	aabb->Draw();
	//}
	//line_->DrawSegment();
	//line_->DrawBezier();
	//line_->DrawCatmullRom();
	/*for (auto& controlPoint : bezierPointSpheres_) {
		controlPoint->Draw();
	}*/
	//for (auto controlPoint : catmullRomPointSpheres_) {
	//	controlPoint->Draw();
	//}
	plane_->Draw();
	/*for (Sphere* sphere : spheres_) {
		sphere->Draw();
	}*/
	/*point1_->Draw();
	point2_->Draw();*/
	//triangle_->WireFrameDraw();
	/*for (auto& obb : obbs_) {
		obb->Draw();
	}*/

	capsule_->Draw();

	//hexagon_->Draw();

	for (auto& sphere : sphereBall_) {
		sphere->Draw();
	}
	//wire_->DrawSegment();
}