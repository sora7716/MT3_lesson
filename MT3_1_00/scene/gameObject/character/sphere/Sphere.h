#pragma once
#include "scene/gameObject/character/Character.h"

class Camera;//前方宣言

class Sphere:Character{

public://構造体
	//スフィアに使う構造体
	typedef struct Material {
		Vector3 center;
		float radius;
		uint32_t color;
	}Material;

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sphere();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sphere();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="sphere">スフィアの素材</param>
	void Initialize(Camera *camera, Material sphere);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// カラーのセッター
	/// </summary>
	/// <param name="color"></param>
	void SetColor(uint32_t color);

private://メンバ変数
	
	Material sphere_;//スフィアの素材

	Camera *camera_;//カメラ

	Vector3 screenA_;//スクリーン座標
	Vector3 screenB_;//スクリーン座標
	Vector3 screenC_;//スクリーン座標
};

