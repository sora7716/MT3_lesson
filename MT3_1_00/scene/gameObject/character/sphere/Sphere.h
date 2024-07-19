#pragma once
#include "scene/gameObject/character/Character.h"

//前方宣言
class Camera;
class Grid;
class Plane;

class Sphere :public Character {

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
	void Initialize(Camera* camera);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

#ifdef _DEBUG
	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="label_center">centerのラベル</param>
	/// <param name="label_radius">radiusのラベル</param>
	void DebugText(const char* label);
#endif

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 当たった時の判定
	/// </summary>
	void OnCollision();

	/// <summary>
	/// カラーのセッター
	/// </summary>
	/// <param name="color"></param>
	void SetColor(uint32_t color);

	/// <summary>
	/// スフィアの素材のゲッター
	/// </summary>
	/// <returns></returns>
	SphereMaterial GetSphereMaterial()const;

	/// <summary>
	/// 平面のセッター
	/// </summary>
	/// <param name="plaen">平面</param>
	void SetPlane(Plane* plane);

	/// <summary>
	/// カメラのゲッター
	/// </summary>
	/// <param name="camera">カメラ</param>
	void SetCamera(Camera* camera);

	/// <summary>
	/// 球の素材のセッター
	/// </summary>
	/// <param name="material">球の素材</param>
	void SetSphere(const SphereMaterial& material);

	/// <summary>
	/// 当たり判定のセッター
	/// </summary>
	/// <param name="isHit">hitフラグ</param>
	void SetIsHit(bool isHit);

private://メンバ関数

	/// <summary>
	/// 色を変える
	/// </summary>
	void ChangeColor();

private://メンバ変数

	Camera* camera_;//カメラ
	SphereMaterial sphere_;//スフィアの素材
	Plane* plane_;//平面
	Vector3 screenA_;//スクリーン座標
	Vector3 screenB_;//スクリーン座標
	Vector3 screenC_;//スクリーン座標
};

