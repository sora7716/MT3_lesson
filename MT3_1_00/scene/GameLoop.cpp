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
	for (int i = 0; i < kHexagonNum; i++) {
		hexagons_[i] = make_unique<Hexagon>();
	}
	//OBB
	for (int i = 0; i < kOBBNum; i++) {
		obbs_[i] = make_unique<OBB>();
	}
	//AABB
	for (int i = 0; i < kAABBNum; i++) {
		aabbs_[i] = make_unique<AABB>();
	}
	//平面
	plane_ = make_unique<Plane>();
	//三角形
	triangle_ = make_unique<Triangle>();
	//球
	for (int i = 0; i < kSphereNum; i++) {
		spheres_[i] = make_unique<Sphere>();
	}
	//カプセル
	capsule_ = make_unique<Capsule>();
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
	hexagonMaterials_[0] = { .center = {0.0f, 0.0f,0.0f},.radius = {1.0f,1.0f},.height = 0.1f };
	hexagonMaterials_[1] = { .center = {2.0f, 0.2f,0.0f},.radius = {1.0f,1.0f},.height = 0.1f };
	hexagonMaterials_[2] = { .center = {-2.0f,0.2f,0.0f},.radius = {1.0f,1.0f},.height = 0.1f };
	hexagonMaterials_[3] = { .center = {0.0f, 0.2f,2.0f},.radius = {1.0f,1.0f},.height = 0.1f };
	for (int i = 0; i < kHexagonNum; i++) {
		hexagons_[i]->Initialize(camera_.get(), move(hexagonMaterials_[i]));
	}
	//OBB
	obbMaterial_[0] = {
		.center = {0.0f,3.0f,0.0f},
		.size = {0.1f,0.1f,0.1f}
	};
	//ボックス
	box_ = {
		.position = obbMaterial_[0].center,
		.velocity = {},
		.acceleration = kGravity,
		.mass = 1.0f,
		.size = obbMaterial_[0].size,
		.color = obbMaterial_[0].color
	};
	/*obbMaterial_[1] = {
		.center = {0,0.0f,5.0f},
	};*/
	for (int i = 0; i < kOBBNum; i++) {
		obbs_[i]->Initialize(camera_.get(), move(obbMaterial_[i]));
	}
	//AABB
	aabbMaterial_[0] = {
		.min{},
		.max{1.0f,1.0f,1.0f}
	};
	/*aabbMaterial_[1] = {
		 .min{1.0f,1.0f,1.0f},
		.max{2.0f,2.0f,2.0f}
	};*/
	for (int i = 0; i < kAABBNum; i++) {
		aabbs_[i]->Initialize(camera_.get(), move(aabbMaterial_[i]));
	}
	//平面
	plane_->Initialize(camera_.get());
	//三角形
	triangleMaterial_ = {
		{{ 0.0f,  1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0f },
		{ -1.0f, -1.0f, 0.0f }},
	};
	triangle_->Initialize(camera_.get(), kWindowWidth, kWindowHeight, move(triangleMaterial_));
	//球
	sphereMaterial_[0] = {
		{0,0,0},
		0.1f
	};
	/*sphrereMaterial_[1] = {
		{1,1,1},
		1.0f
	};*/
	for (int i = 0; i < kSphereNum; i++) {
		spheres_[i]->Initialize(camera_.get(), move(sphereMaterial_[i]));
	}
	//カプセル
	capsuleMaterial_ = {
		{{0,0,0},{0.5f,0.5f,0.5f}},
		1.0f
	};
	capsule_->Initialize(camera_.get(), move(capsuleMaterial_));
}

//更新処理
void GameLoop::Update() {
	// キー入力を受け取る
	memcpy(preKeys_, keys_, 256);
	Novice::GetHitKeyStateAll(keys_);
#ifdef _DEBUG
	DebugText();//デバックテキスト
#endif // _DEBUG


	//カメラ
	camera_->Update(keys_, preKeys_);
	//グリッド線
	grid_->Update();
	//ライン
	line_->Update();
	//六角形
	for (auto& hexagon : hexagons_) {
		hexagon->Update();
	}
	//OBB
	for (auto& obb : obbs_) {
		obb->Update();
	}
	//AABB
	for (auto& aabb : aabbs_) {
		aabb->Update();
	}
	//平面
	plane_->Update();
	//三角形
	triangle_->Update(keys_, preKeys_);
	//球
	for (auto& sphere : spheres_) {
		sphere->Update();
	}
	//カプセル
	capsule_->Updata();



	//衝突判定
	Collider();
	//ボックスの操作
	if (keys_[DIK_SPACE] && !preKeys_[DIK_SPACE] && !isFall_) {
		isFall_ = true;
		box_.velocity.y = kSpeed_.y;
	}
	if (!box_.isHit.left && !box_.isHit.right) {

		if (keys_[DIK_D]) {
			box_.velocity.x = kSpeed_.x;
		}
		else if (keys_[DIK_A]) {
			box_.velocity.x = -kSpeed_.x;
		}
		else {
			if (!isFall_ || box_.isHit.left) {
				box_.acceleration.x = Math::Friction(box_.velocity, box_.mass, box_.miu).x;
			}
		}
	}
	if (keys_[DIK_W]) {
		box_.velocity.z = kSpeed_.z;
	}
	else if (keys_[DIK_S]) {
		box_.velocity.z = -kSpeed_.z;
	}
	else {
		if (!isFall_) {
			box_.acceleration.z = Math::Friction(box_.velocity, box_.mass, box_.miu).z;
		}
	}
	box_.size = obbs_[0]->GetOBBMaterial().size;
	box_.position += box_.velocity * deltaTime;
	box_.velocity.x += box_.acceleration.x * deltaTime;
	box_.velocity.z += box_.acceleration.z * deltaTime;
	if (isFall_) {
		box_.velocity.y += box_.acceleration.y * deltaTime;
	}

	if (isFall_) {
		box_.acceleration = Math::AirResistance(box_.velocity, box_.mass, box_.k);
	}
	obbs_[0]->SetPosition(box_.position);
}

#ifdef _DEBUG
//デバックテキスト
void GameLoop::DebugText() {
	ImGui::Begin("Window");
	//camera_->DebugText();
	/*line_->DebugText();*/
	hexagons_[0]->DebugText("hexagon[0]");
	hexagons_[1]->DebugText("hexagon[1]");
	hexagons_[2]->DebugText("hexagon[2]");
	hexagons_[3]->DebugText("hexagon[3]");
	obbs_[0]->DebagText("obb[0]");
	//obbs_[1]->DebagText("obb[1]");
	//aabbs_[0]->DebugText("aabb[0]");
	//aabbs_[1]->DebugText("aabb[1]");
	//plane_->DebugText();
	//triangle_->DebugText();
	//spheres_[0]->DebugText("sphere[0]");
	//spheres_[1]->DebugText("sphere[1]");
	//capsule_->DebugText();
	ImGui::End();

	ImGui::Begin("box");
	ImGui::DragFloat3("acceleration", &box_.acceleration.x, 0.1f);
	ImGui::DragFloat3("velocity", &box_.velocity.x, 0.1f);
	ImGui::DragFloat3("position", &box_.position.x, 0.1f);
	ImGui::DragFloat3("size", &box_.size.x, 0.1f);
	ImGui::DragFloat("mass", &box_.mass, 0.1f);
	ImGui::DragFloat("miu", &box_.miu, 0.1f);
	if (ImGui::Button("startPos")) {
		box_.position = { 0.0f,4.0f,0.0f };
		box_.velocity = {};
	}
	ImGui::Checkbox("isFall", &isFall_);
	ImGui::End();
}
#endif // _DEBUG

//当たり判定
void GameLoop::Collider() {
	//obbs_[0]->OnCollision(Collision::GetInstance()->IsCollision(obbs_[0].get(),obbs_[1].get()));
	//line_->OnCollision(Collision::GetInstance()->IsCollision(line_->GetSegment(), triangle_->GetTriangleMaterial()));
	/*hexagon_->OnCollision(Collision::GetInstance()->IsCollision(hexagon_.get(), line_.get(),0));
	hexagon_->OnCollision(Collision::GetInstance()->IsCollision(hexagon_.get(), line_.get(),1));*/
	//aabbs_[0]->OnCollision(Collision::GetInstance()->IsCollision(aabbs_[0]->GetAABBMaterial(),plane_->GetPlaneMaterial()));
	//obbs_[0]->OnCollision(Collision::GetInstance()->IsCollision(obbs_[0].get(), plane_->GetPlaneMaterial()));
	for (auto& hexagon : hexagons_) {
		//hexagon->OnCollision(Collision::GetInstance()->IsCollision(hexagon.get(), obbs_[0].get()));
		if (Collision::GetInstance()->IsCollision(hexagon.get(), obbs_[0].get())) {
			//OBBの下の面が当たったかどうか
			if (box_.position.y - box_.size.y > hexagon->GetHexagonMaterial().center.y) {
				box_.isHit.under = true;//当たっている
				box_.velocity.y += 1.0f;
				Math::Reflection(box_.velocity, hexagon->GetHexagonMaterial().normal[3], box_.e, isFall_);
				if (!isFall_) {
					break;
				}
			}
			else {
				box_.isHit.under = false;
			}
			//OBBの上の面が当たったかどうか
			if (box_.position.y + box_.size.y < hexagon->GetHexagonMaterial().center.y) {
				box_.isHit.up = true;
				box_.velocity.y -= 1.0f;
			}
			else {
				box_.isHit.up = false;
			}
		}
		else {
			isFall_ = true;
		}
	}
	ImGui::Checkbox("isHitLeft", &box_.isHit.left);
	for (auto& hexagon : hexagons_) {
		float height = hexagon->GetHexagonMaterial().height;
		Vector3 center = hexagon->GetHexagonMaterial().center;
		float hexagonMinY = -height;
		float hexagonMaxY = center.y + height;
		float boxMinY = box_.position.y - box_.size.y;
		float boxMaxY = box_.position.y + box_.size.y;
		bool range = box_.position.y<hexagonMaxY && box_.position.y>hexagonMinY ||
			center.y<boxMinY && center.y>boxMaxY;
		if (Collision::GetInstance()->IsCollision(hexagon.get(), obbs_[0].get())) {
			if (box_.position.x < hexagon->GetHexagonMaterial().center.x
				&& range && !box_.isHit.up) {
				box_.acceleration.x = 9.8f;
				Math::Reflection(box_.velocity, obbs_[0]->GetOBBMaterial().orientations[0], box_.e);
				box_.isHit.left = true;
			}
			else {
				box_.isHit.left = false;
				box_.acceleration.x = 0.0f;
			}
		}
	}
}

//描画処理
void GameLoop::Draw() {
	//グリッド線
	grid_->Draw();
	//ライン
	//line_->DrawSegment();
	//六角形
	for (auto& hexagon : hexagons_) {
		hexagon->Draw();
	}
	//OBB
	for (auto& obb : obbs_) {
		obb->Draw();
	}
	//AABB
	/*for (auto& aabb : aabbs_) {
		aabb->Draw();
	}*/
	//平面
	//plane_->Draw();
	//三角形
	//triangle_->DrawWireFrame();
	//球
	/*for (auto& sphere : spheres_) {
		sphere->Draw();
	}*/
	//球の通った道を表示
	//line_->DrawObjectRoad(spheres_[0]->GetSphereMaterial().center);
	//line_->DrawObjectRoad(box_.position);
	//カプセル
	//capsule_->Draw();
}