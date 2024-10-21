#pragma once
#include "scene/gameObject/character/Character.h"

//前方宣言
class Camera;
class AABB;

class OBB :public Character {

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	OBB() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OBB() = default;


	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="obbMaterial">obbの素材</param>
	void Initialize(Camera* camera, const OBBMaterial&& obbMaterial);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="type">名前</param>
	void DebagText(const char* type = "obb");

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ワールドマトリックス逆行列のゲッター
	/// </summary>
	/// <returns>ワールドマトリックス逆行列</returns>
	Matrix4x4 GetOBBWorldMatrixInvers()const;

	/// <summary>
	/// サイズのゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetSize()const;

	/// <summary>
	/// OBBのマテリアルのゲッター
	/// </summary>
	/// <returns></returns>
	OBBMaterial GetOBBMaterial()const;

	/// <summary>
	/// ローカルの頂点
	/// </summary>
	/// <returns></returns>
	Vertex2D* GetLocalVertex();

	/// <summary>
	/// 衝突したら
	/// </summary>
	void OnCollision(bool isHit);

	/// <summary>
	/// ポジションのセッター
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const Vector3& pos);

private://メンバ関数

	/// <summary>
	/// 頂点を作成
	/// </summary>
	void MakeVertecies();

private://メンバ変数

	OBBMaterial obb_ = {};//obb
	Matrix4x4 invers_ = {};//obbの逆行列
	Camera* camera_ = nullptr;//カメラ
	AABBMaterial aabb_ = {};//AABBのマテリアル
	Vertex2D localVertecies_[kAABB2DNum] = {};//ローカルの頂点
	Vertex2D screenVertecies_[kAABB2DNum] = {};//スクリーンの頂点
};

