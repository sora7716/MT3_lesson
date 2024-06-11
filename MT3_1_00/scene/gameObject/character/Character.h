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
	/// ローカル座標をスクリーン座標に変換
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="kLocalVertices">ローカル座標</param>
	/// <param name="screenVertices">スクリーン座標</param>
	/// <param name="elementCount">ローカルとスクリーンの要素数</param>
	void ScreenTransform(Camera* camera, const Vector3* kLocalVertices, Vector3* screenVertices, uint32_t elementCount);

protected://メンバ変数
    Matrix4x4 worldMatrix_ = {};//ワールドマトリックス
    Matrix4x4 worldViewProjectionMatrix_ = {};//wvpマトリックス
    Vector3   ndcVertex_ = {};//正規化デバイス座標系
};

