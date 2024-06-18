#pragma once
#include "scene/gameObject/character/Character.h"

class Camera;//前方宣言

class Sphere:Character{

public://メンバ関数

	//スフィアに使う変数
	typedef struct Material {
		Vector3 center;
		float radius;
	}Material;

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
	void Draw(uint32_t color);

private://メンバ変数
	
	Material sphere_ = {};//スフィアの素材

	Camera *camera_ = nullptr;//カメラ

	Vector3 screenA_= {};//スクリーン座標
	Vector3 screenB_ = {};//スクリーン座標
	Vector3 screenC_ = {};//スクリーン座標

};

