#include "Triangle.h"

void Triangle::Initialize(int kWindowWidth, int kWindowHeight, Camera* camera) {
	camera_ = camera;//カメラ
	windowHeight_ = kWindowHeight;//縦幅
	windowWidth_ = kWindowWidth;//横幅
	camera_->Initialize(windowWidth_, windowHeight_);//カメラの初期化
	v1_ = { 1.2f,-3.9f,2.5f };//ベクトル1
	v2_ = { 2.8f,0.4f,-1.3f };//ベクトル2

	//三角ポリゴン
	scale_ = { 1.0f,1.0f,1.0f };        //倍率
	translate_ = { 0.0f,1.0f,0.0f };        //ポジション
	radian_.y = 5.0f / 60.0f;

	//ローカル座標
	triangleMaterial_.kLocalVertices_[(int)Vertex::kTop] = { 0.0f,  1.0f, 0.0f };
	triangleMaterial_.kLocalVertices_[(int)Vertex::kRight] = { 1.0f, -1.0f, 0.0f };
	triangleMaterial_.kLocalVertices_[(int)Vertex::kLeft] = { -1.0f, -1.0f, 0.0f };

	triangleMaterial_.color = WHITE;
}

void Triangle::Update(char* keys, char* preKeys) {
	cross_ = Math::Cross(v1_, v2_);//クロス積の計算

	camera_->Update(keys, preKeys);//カメラの更新処理
	for (uint32_t i = 0; i < 3; i++) {
		CameraScreenTransform(camera_,triangleMaterial_.kLocalVertices_[i], screenVertices_[i]);
	}
	//Transfar(keys, preKeys);//三角形の動き
}

#ifdef _DEBUG
void Triangle::DebugText() {
	ImGui::DragFloat2("VertexTop", &triangleMaterial_.kLocalVertices_[(int)Vertex::kTop].x, 0.01f);
	ImGui::DragFloat2("VertexRight", &triangleMaterial_.kLocalVertices_[(int)Vertex::kRight].x, 0.01f);
	ImGui::DragFloat2("VertexLeft", &triangleMaterial_.kLocalVertices_[(int)Vertex::kLeft].x, 0.01f);
}
#endif // _DEBUG

void Triangle::Draw()const {
	//クロス積
	//ScreenPrintf::VectorScreenPrintf(0, 0, cross_, "Cross");
	//三角ポリゴン
	Novice::DrawTriangle(
		int(screenVertices_[(int)Vertex::kTop].x), int(screenVertices_[(int)Vertex::kTop].y),
		int(screenVertices_[(int)Vertex::kRight].x), int(screenVertices_[(int)Vertex::kRight].y),
		int(screenVertices_[(int)Vertex::kLeft].x), int(screenVertices_[(int)Vertex::kLeft].y),
		RED, kFillModeSolid);
}

void Triangle::WireFrameDraw()const {
	//三角ポリゴン
	Novice::DrawTriangle(
		int(screenVertices_[(int)Vertex::kTop].x), int(screenVertices_[(int)Vertex::kTop].y),
		int(screenVertices_[(int)Vertex::kRight].x), int(screenVertices_[(int)Vertex::kRight].y),
		int(screenVertices_[(int)Vertex::kLeft].x), int(screenVertices_[(int)Vertex::kLeft].y),
		triangleMaterial_.color, kFillModeWireFrame);
}

//衝突時の判定
void Triangle::OnCollisiton() {
	if (triangleMaterial_.isHit) {
		SetColor(RED);
	}
	else {
		SetColor(WHITE);
	}
}

//三角形のマテリアルのゲッター
Triangle::TriangleMaterial Triangle::GetTriangleMaterial() const {
	return triangleMaterial_;
}

//カラーのセッター
void Triangle::SetColor(uint32_t color) {
	triangleMaterial_.color= color;
}

//動き
void Triangle::Transfar(char* keys, char* preKeys) {
	bool left = keys[DIK_A] && preKeys[DIK_A];
	bool right = keys[DIK_D] && preKeys[DIK_D];
	bool front = keys[DIK_S] && preKeys[DIK_S];
	bool behind = keys[DIK_W] && preKeys[DIK_W];
	GameObject::Scale(behind, front);//拡縮
	GameObject::Rotate();//回転
	GameObject::TranslateX(left, right, 1.0f);//移動
}
