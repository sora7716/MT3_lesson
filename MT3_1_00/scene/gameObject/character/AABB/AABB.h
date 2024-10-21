#pragma once
#include "scene/gameObject/character/Character.h"

class Camera;
//AABBクラス
class AABB :public Character {

public://メンバ関数

	/// <summary>
	/// コンストラクター
	/// </summary>
	AABB();

	/// <summary>
	/// デストラクター
	/// </summary>
	~AABB();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="aabb">aabb</param>
	void Initialize(Camera* camera, const AABBMaterial&& aabb);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 衝突したときの判定
	/// </summary>
	void OnCollision(bool isHit);

#ifdef _DEBUG
	void DebugText(const char* type = "aabb");
#endif // _DEBUG

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()const;

	/// <summary>
	/// 衝突したかどうかのセッター
	/// </summary>
	/// <param name="isHit">セットしたいフラグ</param>
	void SetIsHit(bool isHit);

	/// <summary>
	/// 色のセッター
	/// </summary>
	/// <param name="color">セットしたいカラー</param>
	void SetColor(uint32_t color);

	/// <summary>
	/// ローカル座標のセッター
	/// </summary>
	/// <param name="local">ローカル座標</param>
	void SetLocalVertex2D(Vertex2D local);

	/// <summary>
	/// aabbのセッター
	/// </summary>
	/// <param name="min">最小</param>
	/// <param name="max">最大</param>
	void SetAABB(Vector3 min, Vector3 max);

	/// <summary>
	/// AABBの素材のゲッター
	/// </summary>
	/// <returns></returns>
	AABBMaterial GetAABBMaterial()const;

private://メンバ変数
	AABBMaterial aabb_ = {};
	Camera* camera_ = nullptr;
	Vertex2D localVertecies_[kAABB2DNum] = {};
	Vertex2D screenVertecies_[kAABB2DNum] = {};

};

