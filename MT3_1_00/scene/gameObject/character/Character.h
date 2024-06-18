#pragma once
#include "scene/gameObject/GameObject.h"
#include "scene/gameObject/camera/Camera.h"
class Character:public GameObject{

protected://メンバ関数
	
    /// <summary>
    /// world*viewProjectionを求める
    /// </summary>
    /// <param name="camera">カメラ</param>
    void WvpMatrix(Camera* camera);

    /// <summary>
    /// world*viewProjectionを求める(拡縮回転移動を宣言)
    /// </summary>
    /// <param name="camera">カメラ</param>
    /// <param name="scele">倍率</param>
    /// <param name="rotate">角度</param>
    /// <param name="translate">移動</param>
    void WvpMatrix(Camera* camera,Vector3 scale,Vector3 rotate,Vector3 translate);

    /// <summary>
    /// world*viewProjectionを求める(拡縮回転移動を宣言)戻り値あり
    /// </summary>
    /// <param name="camera">カメラ</param>
    /// <param name="scele">倍率</param>
    /// <param name="rotate">角度</param>
    /// <param name="translate">移動</param>
    Matrix4x4 WorldViewProjectionMatrix(Camera* camera, Vector3 scale, Vector3 rotate, Vector3 translate);


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
    /// <param name="ndcVertex">正規化デバイス</param>
    /// <param name="kLocalVertices">ローカル座標</param>
    /// <param name="screenVertices">スクリーン座標</param>
    void CameraScreenTransform(Camera* camera,const Vector3& kLocalVertices, Vector3& screenVertices);


protected://メンバ変数
    Matrix4x4 worldMatrix_ = {};//ワールドマトリックス
    Matrix4x4 worldViewProjectionMatrix_ = {};//wvpマトリックス
    Vector3   ndcVertex_ = {};//正規化デバイス座標系
};

