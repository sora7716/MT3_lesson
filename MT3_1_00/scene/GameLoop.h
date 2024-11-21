#pragma once
#include "scene/gameObject/GameObject.h"
#include"scene/gameObject/camera/Camera.h"
#include"scene/gameObject/character/triangle/Triangle.h"
#include"scene/gameObject/character/grid/Grid.h"
#include "scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/point/Point.h"
#include "scene/gameObject/character/plane/Plane.h"


class GameLoop {
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
	/// ゲームループ
	/// </summary>
	void Loop();
public://静的メンバ変数
	static inline const char kWindowTitle[] = "GC2B_01_イイヅカ_ソラ_title";//タイトルバー
	static inline const int kKeysNums = 256;//読み込むキーの数
	static inline const int kWindowWidth = 1280;//画面の横幅
	static inline const int kWindowHeight = 720;//画面の縦幅
	static inline const int kSphereNum = 1;//スフィアの数
private://メンバ変数
	char keys_[kKeysNums];
	char preKeys_[kKeysNums];
	Camera* camera_;
	Triangle* triangle_;
	Grid* grid_;

	Sphere* sphere_[kSphereNum];

	Sphere* point1_;
	Sphere* point2_;
	Point* line_;

	Plane* plane_;

private://メンバ関数

	/// <summary>
	/// 生成
	/// </summary>
	void Create();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
};

