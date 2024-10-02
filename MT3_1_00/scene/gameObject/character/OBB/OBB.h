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
	/// <param name="aabb">aabb</param>
	void Initialize(Camera* camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebagText(const char* type);

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
	/// 衝突したら
	/// </summary>
	void OnCollision(bool isHit);

private://メンバ関数

	/// <summary>
	/// 頂点を作成
	/// </summary>
	void MakeVertecies();

private://メンバ変数

	ObbMaterial obb_ = {};//obb
	Matrix4x4 invers_ = {};//obbの逆行列
	Camera* camera_ = nullptr;//カメラ
	AABBMaterial aabb_ = {};//AABBのマテリアル
	AABBVertex2D localVertecies_[kAABB2DNum] = {};//ローカルの頂点
	AABBVertex2D screenVertecies_[kAABB2DNum] = {};//スクリーンの頂点
};

