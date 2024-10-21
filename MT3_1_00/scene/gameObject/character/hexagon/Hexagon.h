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
	void Initialize(Camera* camera, const HexagonMaterial&& hexagonMaterial);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="name">名前</param>
	void DebugText(const char* name = "hexagon");

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
	/// <param name="i">表か裏か</param>
	/// <returns></returns>
	Vector3* GetVertex(int i);

	/// <summary>
	/// 六角形の素材のゲッター
	/// </summary>
	HexagonMaterial GetHexagonMaterial();

private://メンバ関数

	/// <summary>
	/// 法線ベクトルを作成
	/// </summary>
	void CreateNormal();

public://静的メンバ変数

	static inline const int kVertexNum = 6;
	static inline const int Surface = 2;

private://メンバ変数
	Camera* camera_ = nullptr;//カメラ
	HexagonMaterial hexagon_;//六角形を作成の素材
	Vector3 vertex[Surface][kVertexNum] = {};//頂点
	Vector3 screenVertex[Surface][kVertexNum] = {};//スクリーン座標の頂点
};

