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
	void Initialize(Camera* camera, const AABBMaterial& aabb);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

#ifdef _DEBUG
	void DebugText(const char* type);
#endif // _DEBUG

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private://メンバ変数
	AABBMaterial aabb_ = {};
	Camera* camera_ = nullptr;
	AABBVertex2D localVertecies_[kAABB2DNum] = {};
	AABBVertex2D screenVertecies_[kAABB2DNum] = {};

};

