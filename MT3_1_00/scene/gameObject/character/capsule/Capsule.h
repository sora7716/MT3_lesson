#pragma once
#include"scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/line/Line.h"

#include <memory>
/// <summary>
/// カプセルを作成
/// </summary>
class Capsule :Character{
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
	void Initialize(Camera* camera,const CapsuleMaterial&& capsule);

	/// <summary>
	/// 更新
	/// </summary>
	void Updata();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private://メンバ変数
	Camera* camera_ = nullptr;//カメラ
	CapsuleMaterial capsule_;//カプセル
	std::unique_ptr<Line> line_ = nullptr;//線分
	std::unique_ptr<Sphere> sphere_[2] = nullptr;//球
};

