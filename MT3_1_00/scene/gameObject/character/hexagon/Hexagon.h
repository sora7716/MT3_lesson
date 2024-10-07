#pragma once
#include "scene/gameObject/character/Character.h"

/// <summary>
/// 六角形
/// </summary>
class Hexagon :Character {
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Hexagon() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Hexagon() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="hexagonMaterial">六角形を作成するときに使用する素材</param>
	void Initialize(Camera* camera, HexagonMaterial hexagonMaterial);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="name">名前</param>
	void DebugText(const char* name);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
    /// 衝突したとき
    /// </summary>
	/// <param name="isHit">衝突したかどうか</param>
	void OnCollision(bool isHit);

	/// <summary>
	/// 頂点のゲッター
	/// </summary>
	Vector3* GetVertex();

	/// <summary>
	/// 六角形の素材のゲッター
	/// </summary>
	HexagonMaterial GetHexagonMaterial();

private://メンバ変数
	Camera* camera_ = nullptr;//カメラ
	HexagonMaterial hexagon_;//六角形を作成の素材
	Vector3 vertex[6] = {};//頂点
	Vector3 screenVertex[6] = {};//スクリーン座標の頂点
};

