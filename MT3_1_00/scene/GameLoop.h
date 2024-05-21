#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "scene/func/Math.h"
#include "scene/func/ScreenPrintf.h"
#include "scene/func/Aithmetic.h"

class GameLoop
{
public://メンバ関数

	/// <summary>
	/// コンストラクター
	/// </summary>
	GameLoop();

	/// <summary>
	/// デストラクター
	/// </summary>
	~GameLoop();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// ゲームループ
	/// </summary>
	void Loop();
public://静的メンバ変数
	static inline const char kWindowTitle[]  = "GC2B_01_イイヅカ_ソラ_title";//タイトルバー
	static inline const int kKeysNums        =  256;//読み込むキーの数
	static inline const int kWindowWidth     = 1280;//画面の横幅
	static inline const int kWindowHeight    =  720;//画面の縦幅

private://メンバ変数
	char keys[kKeysNums]    = { 0 };
	char preKeys[kKeysNums] = { 0 };

	MyVector3 v1_ = {};//ベクトル1
	MyVector3 v2_ = {};//ベクトル2

	MyVector3 scale_[2]     = {};//倍率
	MyVector3 rotate_[2]    = {};//角度
	MyVector3 translate_[2] = {};//ポジション
	MyVector3 theta[2]      = {};//回転速度

	MyVector3 cross = {};//クロス積

	MyVector3 kLocalVertices_[3] = {};//ローカル座標
	MyVector3 screenVertices_[3] = {};//スクリーン座標

	MyMatrix4x4 worldMatrix               = {};//ワールドマトリックス
	MyMatrix4x4 cameraMatrix              = {};//カメラマトリックス
	MyMatrix4x4 viewMatrix                = {};//ビューマトリックス
	MyMatrix4x4 projectionMatrix          = {};//同次クリップ空間
	MyMatrix4x4 worldViewProjectionMatrix = {};//wvpマトリックス
	MyMatrix4x4 viewportMatrix            = {};//ビューポートマトリックス
};

