#pragma once
#include "scene/gameObject/GameObject.h"
#include "scene/gameObject/camera/Camera.h"
class Triangle:public GameObject{

public://メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="kWindowWidth">画面の横幅</param>
	/// <param name="kWindowHeight">画面の縦幅</param>
	void Initialize(int kWindowWidth, int kWindowHeight, Camera*camera);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys">keys</param>
	/// <param name="preKeys">preKeys</param>
	void Update(char *keys,char *preKeys)override;

	/// <summary>
	/// 拡大
	/// </summary>
	/// <param name="keys">keys</param>
	/// <param name="preKeys">preKeys</param>
	void Scale(char* keys, char* preKeys)override;

	/// <summary>
	/// 回転
	/// </summary>
	void Rotation()override;

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="keys">keys</param>
	/// <param name="preKeys">preKeys</param>
	void Transfer(char *keys,char *preKeys)override;

	/// <summary>
	/// レンダリングパイプライン
	/// </summary>
	void RenderingPipeline()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;

private://メンバ変数

	Camera* camera_ = nullptr;

	MyVector3 v1_    = {};//ベクトル1
	MyVector3 v2_    = {};//ベクトル2
	MyVector3 cross_ = {};//クロス積

	MyVector3 kLocalVertices_[3] = {};//ローカル座標
	MyVector3 screenVertices_[3] = {};//スクリーン座標

	MyMatrix4x4 worldMatrix_ = {};//ワールドマトリックス
	MyMatrix4x4 worldViewProjectionMatrix = {};//wvpマトリックス
	MyVector3 ndcVertex={};
};

