#include <Novice.h>
#include "func/Math.h"
#include "func/ScreenPrintf.h"
#include "func/Aithmetic.h"
#define _USE_MATH_DEFINES
#include <cmath>

const char kWindowTitle[] = "GC2B_01_イイヅカ_ソラ_title";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;
enum {
	triangle,
	camera,
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };

	Vector3 scale[2]     = { {1.0f,1.0f,1.0f} ,{1.0f,1.0f,1.0f} };
	Vector3 rotate[2]    = {};
	Vector3 translate[2] = {};

	Vector3 kLocalVertices[3] ;
	kLocalVertices[0] = {  0.0f, 0.0f, -0.1f };
	kLocalVertices[1] = { -0.5f, 1.0f, -0.1f };
	kLocalVertices[2] = {  0.5f, 1.0f, -0.1f };
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		MyVector3 cross = Math::Cross(v1, v2);

		rotate[triangle].y += 1.0f / 45.0f * float(M_PI) / 180.0f;

		MyMatrix4x4 worldMatrix               = Math::MakeAffineMatrix(scale[triangle], rotate[triangle], translate[triangle]);
		MyMatrix4x4 cameraMatrix              = Math::MakeAffineMatrix(scale[camera],   rotate[camera],   translate[camera]);
		MyMatrix4x4 viewMatrix                = Math::Inverse(cameraMatrix);
		MyMatrix4x4 projectionMatrix          = Math::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		MyMatrix4x4 worldViewProjectionMatrix = worldMatrix*(viewMatrix*projectionMatrix);
		MyMatrix4x4 viewportMatrix            = Math::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Math::Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Math::Transform(ndcVertex, viewportMatrix);
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		ScreenPrintf::VectorScreenPrintf(0, 0, cross, "Cross");
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y),
			RED, kFillModeSolid);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
