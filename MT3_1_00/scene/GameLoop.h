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
#include "scene/gameObject/character/capsule/Capsule.h"
#include "scene/gameObject/character/hexagon/Hexagon.h"

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
	static inline const int kSphereNum = 2;//スフィアの数
	static inline const int kAABBNum = 1;//AABBの数
	static inline const int kOBBNum = 2;//OBBの数
private://メンバ変数
	char keys_[kKeysNums]{};
	char preKeys_[kKeysNums]{};
	Camera* camera_ = nullptr;
	Triangle* triangle_ = nullptr;
	Grid* grid_ = nullptr;

	Sphere* spheres_[kSphereNum] = {};

	Sphere* point1_ = nullptr;
	Sphere* point2_ = nullptr;
	std::unique_ptr<Line> line_ = nullptr;
	GameObject::Segment segment_ = { {-0.45f,0.41f,0.0f},{1.0f,0.58f,0.0f} };
	Vector3 bezierControlPoints[3] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
	};
	std::vector<Vector3>catmullRomPoints_{
		{-1.07f,0.13f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
		{-0.53f,-0.26f,-0.15f},
	};
	std::unique_ptr<Sphere>bezierPointSpheres_[3] = { nullptr };
	std::vector<Sphere*>catmullRomPointSpheres_;

	Plane* plane_ = nullptr;

	Collision* collision_ = nullptr;

	AABB* aabbs_[kAABBNum] = { nullptr };

	std::unique_ptr<OBB>obbs_[kOBBNum] = { nullptr };
	GameObject::OBBMaterial obbMaterial_[kOBBNum] = {};

	std::unique_ptr<Capsule>capsule_ = nullptr;
	GameObject::CapsuleMaterial capsuleMaterial_ = {};

	std::unique_ptr<Hexagon>hexagon_ = nullptr;
	GameObject::HexagonMaterial hexagonMateiral_ = {};

	Math::Spring spring_{};
	Math::Ball ball_{};
	GameObject::SphereMaterial sphereBallMaterial_{};
	std::unique_ptr<Sphere>sphreBall_ = nullptr;
	GameObject::Segment wireSegment_ = {};
	std::unique_ptr<Line>wire_ = nullptr;
	Vector3 centerPos_{};
	Vector2 centerRadius_ = {};
	Math::Pendulum pendulum_ = {};
	Math::ConicalPendulum conicalPendulum_ = {};

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

