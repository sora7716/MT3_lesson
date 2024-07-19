#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#include <Vector3.h>
#include "scene/gameObject/GameObject.h"
//カメラの前方宣言
class Camera;
class Grid;

class Plane:public GameObject{
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
	void Initialize(Camera* camera);

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
	/// 平面の素材のゲッター
	/// </summary>
	/// <returns></returns>
	const PlaneMaterial& GetPlaneMaterial();

	/// <summary>
	///  平面の素材のセッター
	/// </summary>
	/// <param name="material">平面の素材</param>
	void SetPlane(const PlaneMaterial&material);

private://メンバ関数

	/// <summary>
	/// 垂直
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	Vector3 Perpendicular(const Vector3& v);

private://メンバ変数
	Camera* camera_;//カメラ
	PlaneMaterial plane_;//素材
};

