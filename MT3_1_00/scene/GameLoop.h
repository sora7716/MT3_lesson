#pragma once
#include "scene/gameObject/GameObject.h"
#include"scene/gameObject/camera/Camera.h"
#include"scene/gameObject/character/triangle/Triangle.h"
#include"scene/gameObject/character/grid/Grid.h"
#include "scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/line/Line.h"
#include "scene/gameObject/character/plane/Plane.h"
#include "scene/func/collision/Collision.h"
#include "scene/gameObject/character/AABB/AABB.h"
#include "scene/gameObject/character/OBB/OBB.h"

#include <memory>

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
	static inline const int kAABBNum = 1;//AABBの数k
private://メンバ変数
	char keys_[kKeysNums]{};
	char preKeys_[kKeysNums]{};
	Camera* camera_ = nullptr;
	Triangle* triangle_ = nullptr;
	Grid* grid_ = nullptr;

	Sphere* spheres_[kSphereNum] = {};

	Sphere* point1_ = nullptr;
	Sphere* point2_ = nullptr;
	Line* line_ = nullptr;

	Plane* plane_ = nullptr;

	Collision* collision_ = nullptr;

	AABB* aabbs_[kAABBNum] = { nullptr };

	std::unique_ptr<OBB>obb_ = nullptr;
	GameObject::OBBMaterial obbMaterial_ = {};

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

#ifdef _DEBUG
	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();
#endif // _DEBUG
	/// <summary>
	/// 当たり判定
	/// </summary>
	void Collider();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
};

