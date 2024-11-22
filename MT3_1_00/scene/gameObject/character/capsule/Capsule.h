#pragma once
#include"scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/line/Line.h"

#include <memory>
/// <summary>
/// カプセルを作成
/// </summary>
class Capsule :Character {
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Capsule() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Capsule() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="capsule">カプセルの素材</param>
	void Initialize(Camera* camera, const CapsuleMaterial&& capsule);

	/// <summary>
	/// 更新
	/// </summary>
	void Updata();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText(const char* name = "capsule");

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// カプセルの素材のセッター
	/// </summary>
	/// <param name="capsuleMaterial">カプセルの素材</param>
	void SetCapsuleMaterial(const CapsuleMaterial& capsuleMaterial);

	/// <summary>
	/// カプセルの素材のゲッター
	/// </summary>
	/// <returns>カプセルの素材</returns>
	CapsuleMaterial GetCapsuleMaterial();

	/// <summary>
	/// 衝突したら
	/// </summary>
	/// <param name="isHit">衝突したかどうか</param>
	void OnCollision(bool isHit);

public://静的メンバ変数

	static inline const int kLineNum = 4;

private://メンバ変数
	Camera* camera_ = nullptr;//カメラ
	CapsuleMaterial capsule_;//カプセル
	std::unique_ptr<Line> lines_[kLineNum] = { nullptr };//線分
	std::unique_ptr<Line> centerLine_ = nullptr;//真ん中の線
	std::unique_ptr<Sphere> sphere_[2] = { nullptr };//球
};

