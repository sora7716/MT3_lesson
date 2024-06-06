#pragma once
#include "scene/gameObject/GameObject.h"
#include"scene/gameObject/camera/Camera.h"
#include"scene/gameObject/character/triangle/Triangle.h"
#include"scene/gameObject/character/grid/Grid.h"

class GameLoop{
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
	char keys_[kKeysNums]    = { 0 };
	char preKeys_[kKeysNums] = { 0 };
	Camera* camera_     = nullptr;
	Triangle* triangle_ = nullptr;
	Grid* grid_ = nullptr;
};

