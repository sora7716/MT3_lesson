#include "GameLoop.h"

enum {
	camera,
	triangle,
};

//コンストラクター
GameLoop::GameLoop(){
}

//デストラクター
GameLoop::~GameLoop(){
}

//初期化処理
void GameLoop::Initialize() {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	v1_.SetVector({ 1.2f,-3.9f,2.5f });
	v2_.SetVector({ 2.8f,0.4f,-1.3f });

	scale_[camera].SetVector({ 1.0f,1.0f,1.0f });
	scale_[triangle].SetVector({ 1.0f,1.0f,1.0f });
	translate_[triangle].SetVector({ 0.0f,0.5f,5.0f });
	translate_[camera].SetVector({ 0.0f,0.0f,-5.0f });

	theta[triangle].SetVector({ 0.0f,1.0f / 30.0f,0.0f });
	kLocalVertices_[0].SetVector({ -0.5f, -0.5f, 0.0f });
	kLocalVertices_[1].SetVector({  0.0f,  0.5f, 0.0f });
	kLocalVertices_[2].SetVector({  0.5f, -0.5f, 0.0f });
}

//更新処理
void GameLoop::Update(){
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	cross = Math::Cross(v1_, v2_);
	rotate_[triangle] += theta[triangle];

	worldMatrix               = Math::MakeAffineMatrix(scale_[triangle].GetVector(), rotate_[triangle].GetVector(), translate_[triangle].GetVector());
	cameraMatrix              = Math::MakeAffineMatrix(scale_[camera].GetVector(), rotate_[camera].GetVector(), translate_[camera].GetVector());
	viewMatrix                = ~cameraMatrix;
	projectionMatrix          = Math::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	worldViewProjectionMatrix = worldMatrix * (viewMatrix * projectionMatrix);
	viewportMatrix            = Math::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	for (uint32_t i = 0; i < 3; ++i) {
		MyVector3 ndcVertex  = Math::Transform(kLocalVertices_[i], worldViewProjectionMatrix);
		screenVertices_[i]   = Math::Transform(ndcVertex, viewportMatrix);
	}
}

//描画処理
void GameLoop::Draw(){
	ScreenPrintf::VectorScreenPrintf(0, 0, cross, "Cross");
	Novice::DrawTriangle(
		int(screenVertices_[0].GetVector().x), int(screenVertices_[0].GetVector().y),
		int(screenVertices_[1].GetVector().x), int(screenVertices_[1].GetVector().y),
		int(screenVertices_[2].GetVector().x), int(screenVertices_[2].GetVector().y),
		RED, kFillModeSolid);
}

//ゲームループ
void GameLoop::Loop(){

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
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

}
