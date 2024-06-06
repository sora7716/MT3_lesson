#pragma once
#include "scene/gameObject/GameObject.h"
#include "scene/gameObject/camera/Camera.h"
class Character:public GameObject{

protected://メンバ関数
	
	/// <summary>
    /// ローカル座標をスクリーン座標に変換
    /// </summary>
    /// <param name="camera">カメラ</param>
    /// <param name="worldMatrix">ワールドマトリックス</param>
    /// <param name="worldViewProjectionMatrix">ワールドビューマトリックス</param>
    /// <param name="kLocalVertices">ローカル座標</param>
    /// <param name="ndcVertex">ndcVertex</param>
    /// <param name="screenVertices">スクリーンの頂点</param>
	/// <param name="verticesNum">頂点の数</param>
	void ScreenTransform(Camera* camera, MyMatrix4x4& worldMatrix, MyMatrix4x4& worldViewProjectionMatrix, const MyVector3* kLocalVertices, MyVector3& ndcVertex, MyVector3* screenVertices, uint32_t verticesNum);

protected://メンバ変数
	
};

