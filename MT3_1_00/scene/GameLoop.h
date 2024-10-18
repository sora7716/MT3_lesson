#pragma once
#include "scene/gameObject/GameObject.h"
#include "scene/gameObject/camera/Camera.h"
#include "scene/gameObject/character/OBB/OBB.h"
#include "scene/gameObject/character/hexagon/Hexagon.h"
#include "scene/gameObject/character/line/Line.h"
#include "scene/gameObject/character/grid/Grid.h"
#include "scene/gameObject/character/AABB/AABB.h"
#include "scene/gameObject/character/capsule/Capsule.h"
#include "scene/gameObject/character/plane/Plane.h"
#include "scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/triangle/Triangle.h"
#include "scene/func/collision/Collision.h"
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

public://静的メンバ変数
	static inline const char kWindowTitle[] = "GC2B_01_イイヅカ_ソラ_title";//タイトルバー
	static inline const int kKeysNums = 256;//読み込むキーの数
	static inline const int kWindowWidth = 1280;//画面の横幅
	static inline const int kWindowHeight = 720;//画面の縦幅
	static inline const int kOBBNum = 1;//OBBの数
	static inline const int kAABBNum = 2;//AABBの数
	static inline const int kSphereNum = 1;//球の数
private://メンバ変数
	char keys_[kKeysNums]{};
	char preKeys_[kKeysNums]{};
	//カメラ
	std::unique_ptr<Camera>camera_ = nullptr;
	//ライン
	std::unique_ptr<Line>line_ = nullptr;
	GameObject::Segment segment_ = {};
	//六角形
	std::unique_ptr<Hexagon>hexagon_ = nullptr;
	GameObject::HexagonMaterial hexagonMaterial_ = {};
	//OBB
	std::unique_ptr<OBB>obbs_[kOBBNum] = { nullptr };
	GameObject::OBBMaterial obbMaterial_[kOBBNum] = {};
	//グリッド線
	std::unique_ptr<Grid>grid_ = nullptr;
	//AABB
	std::unique_ptr<AABB>aabbs_[kAABBNum] = { nullptr };
	GameObject::AABBMaterial aabbMaterial_[kAABBNum] = {};
	//平面
	std::unique_ptr<Plane>plane_ = nullptr;
	GameObject::PlaneMaterial planeMaterial_ = {};
	//三角形
	std::unique_ptr<Triangle>triangle_ = nullptr;
	GameObject::TriangleMaterial triangleMaterial_ = {};
	//球
	std::unique_ptr<Sphere>spheres_[kSphereNum] = { nullptr };
	GameObject::SphereMaterial sphrereMaterial_[kSphereNum] = {};
	//カプセル
	std::unique_ptr<Capsule>capsule_ = nullptr;
	GameObject::CapsuleMaterial capsuleMaterial_ = {};
};

