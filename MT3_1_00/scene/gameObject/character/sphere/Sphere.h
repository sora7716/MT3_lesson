#pragma once
#include "scene/gameObject/character/Character.h"

//前方宣言
class Camera;
class Grid;
class Plane;

class Sphere :public Character {

public://構造体
	//スフィアに使う構造体
	typedef struct Material {
		Vector3 center;
		float radius;
		uint32_t color;
		bool isHit;
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
	/// <param name="sphere">スフィアの素材{positon,radius,color}</param>
	void Initialize(Camera* camera, Grid* grid, Material sphere);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="label_center">centerのラベル</param>
	/// <param name="label_radius">radiusのラベル</param>
	void DebugText(const char* label_center, const char* label_radius, const char* label_Rotate);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 当たり判定(球と球)
	/// </summary>
	/// <param name="sphere">別のスフィア</param>
	void IsCollision(const Material& target, const Vector3& worldPosition);

	/// <summary>
	/// 当たり判定(球と平面)
	/// </summary>
	/// <param name="sphere">別のスフィア</param>
	void IsCollision(Sphere* sphere, Plane* plane);

	/// <summary>
	/// カラーのセッター
	/// </summary>
	/// <param name="color"></param>
	void SetColor(uint32_t color);

	/// <summary>
	/// スフィアの素材のゲッター
	/// </summary>
	/// <returns></returns>
	Material GetSphereMaterial();

	/// <summary>
	/// 平面のセッター
	/// </summary>
	/// <param name="plaen">平面</param>
	void SetPlane(Plane* plane);

	/// <summary>
	/// グリッド線のゲッター
	/// </summary>
	/// <param name="grid">グリッド線</param>
	void SetGrid(Grid* grid);

	/// <summary>
	/// カメラのゲッター
	/// </summary>
	/// <param name="camera">カメラ</param>
	void SetCamera(Camera* camera);

	/// <summary>
	/// isHitのセッター
	/// </summary>
	/// <param name="IsHit"></param>
	void SetIsHit(const bool& isHit);

private://メンバ関数

	/// <summary>
	/// 色を変える
	/// </summary>
	void ChangeColor();

private://メンバ変数

	Camera* camera_;//カメラ
	Grid* grid_;//グリッド線
	Material sphere_;//スフィアの素材
	Plane* plane_;//平面
	Vector3 screenA_;//スクリーン座標
	Vector3 screenB_;//スクリーン座標
	Vector3 screenC_;//スクリーン座標
};

