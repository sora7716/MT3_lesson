#pragma once
#include "scene/gameObject/GameObject.h"
#include "scene/gameObject/camera/Camera.h"
class Character :public GameObject {

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Character() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Character() = default;

protected://メンバ関数

	/// <summary>
	/// world*viewProjectionを求める
	/// </summary>
	/// <param name="camera">カメラ</param>
	void WvpMatrix(Camera* camera);

	/// <summary>
	/// world*viewProjectionを求める
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="viewportMatrix">ビューポート</param>
	void WvpMatrix(const Matrix4x4& viewProjection);

	/// <summary>
	/// WvpMatirx
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="scale">倍率</param>
	/// <param name="rotate">角度</param>
	/// <param name="translate">ポジション</param>
	void WvpMatrix(Camera* camera, Vector3& scale, Vector3& rotate, Vector3& translate);

	/// <summary>
    /// ワールドビュープロジェクションだけの計算
    /// </summary>
	/// <param name="camera">カメラ</param>
	void WorldViewProjection(Camera *camera);


	/// <summary>
	/// ワールドビュープロジェクションだけの計算
	/// </summary>
	/// <param name="camera">カメラ</param>
	void OBBWvpMatrix(const Camera* camera);

	/// <summary>
	/// world*viewProjectionを求める(拡縮回転移動を宣言)戻り値あり
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="scele">倍率</param>
	/// <param name="rotate">角度</param>
	/// <param name="translate">移動</param>
	Matrix4x4 WorldViewProjectionMatrix(Camera* camera, Vector3 scale, Vector3 rotate, Vector3 translate)const;


	/// <summary>
	/// ローカル座標をスクリーン座標に変換
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="kLocalVertices">ローカル座標</param>
	/// <param name="screenVertices">スクリーン座標</param>
	void ScreenTransform(Camera* camera, const Vector3& kLocalVertices, Vector3& screenVertices);

	/// <summary>
	/// ローカル座標をスクリーン座標に変換
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="kLocalVertices">ローカル座標</param>
	/// <param name="screenVertices">スクリーン座標</param>
	/// <param name="scele">倍率</param>
	/// <param name="rotate">角度</param>
	/// <param name="translate">移動</param>
	void ScreenTransform(Camera* camera, const Vector3& kLocalVertices, Vector3& screenVertices, Vector3& scale, Vector3& rotate, Vector3& translate);

	/// <summary>
	/// ローカル座標をスクリーン座標に変換
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="kLocalVertices">ローカル座標</param>
	/// <param name="screenVertices">スクリーン座標</param>
	void CameraScreenTransform(Camera* camera, const Vector3& kLocalVertices, Vector3& screenVertices);

	/// <summary>
	/// OBB空間に変換
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="local">ローカル座標</param>
	/// <param name="screen">スクリーン座標</param>
	void OBBTransform(const Camera* camera, const Vector3& local, Vector3& screen);

public://メンバ関数
	/// <summary>
	/// ワールドビュープロジェクションのゲッター
	/// </summary>
	/// <returns></returns>
	const Matrix4x4& GetWorldViewProjection();

	/// <summary>
	/// ワールドマトリックスのゲッター
	/// </summary>
	/// <returns></returns>
	const Matrix4x4& GetWorldMatrix();

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	/// <returns></returns>
	const Vector3 GetWorldPosition();

protected://メンバ変数
	Matrix4x4 worldMatrix_ = {};//ワールドマトリックス
	Matrix4x4 worldViewProjectionMatrix_ = {};//wvpマトリックス
	Vector3   ndcVertex_ = {};//正規化デバイス座標系
};

