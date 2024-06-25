﻿#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <Vector3.h>
//カメラの前方宣言
class Camera;

class Plane {

public://構造体
	//平面の構造体
	typedef struct Material {
		Vector3 normal;
		float distance;
		uint32_t color;
	}Material;
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Plane();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Plane();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="plane">平面の素材{normal,distance,color}</param>
	void Initialize(Camera* camera, const Material& plane);

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

private://メンバ関数
	Vector3 Perpendicular(const Vector3& v);

private://メンバ変数
	Camera* camera_;//カメラ
	Material plane_;//素材
};

