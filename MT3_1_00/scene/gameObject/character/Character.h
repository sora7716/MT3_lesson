#pragma once
#include "scene/gameObject/GameObject.h"
#include "scene/gameObject/camera/Camera.h"
class Character:public GameObject{

protected://メンバ関数
	
	/// <summary>
	/// ローカルをスクリーンに座標変換
	/// </summary>
	/// <param name="camera">カメラ</param>
	void ScreenTransform(Camera* camera);

protected://メンバ変数
	MyVector3 kLocalVertices_[3] = {};//ローカル座標
	MyVector3 screenVertices_[3] = {};//スクリーン座標
	
	MyMatrix4x4 worldMatrix_              = {};//ワールドマトリックス
	MyMatrix4x4 worldViewProjectionMatrix = {};//wvpマトリックス
	MyVector3   ndcVertex                 = {};//正規化デバイス座標系
};

