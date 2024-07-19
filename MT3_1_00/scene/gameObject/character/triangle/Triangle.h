#pragma once
#include "scene/gameObject/character/Character.h"
class Triangle:public Character{

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
	/// <param name="keys">現在の押しているキー</param>
	/// <param name="preKeys">過去に押しているキー</param>
	void Update(char *keys,char *preKeys);

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()const;

	/// <summary>
	/// 描画ワイヤーフレーム
	/// </summary>
	void WireFrameDraw()const;

	/// <summary>
	/// 衝突時の判定
	/// </summary>
	void OnCollisiton();

	/// <summary>
	/// 三角形のマテリアルのゲッター
	/// </summary>
	/// <returns></returns>
	TriangleMaterial GetTriangleMaterial()const;

	/// <summary>
	/// カラーのセッター
	/// </summary>
	/// <param name="color"></param>
	void SetColor(uint32_t color);
private://メンバ変数

	Camera* camera_ = nullptr;

	Vector3 v1_    = {};//ベクトル1
	Vector3 v2_    = {};//ベクトル2
	Vector3 cross_ = {};//クロス積
	
	Vector3 normalize_ = {};
	Vector3 viewVector_ = {};
	float disappear_ = 0;

	TriangleMaterial triangleMaterial_ = {};//三角形のマテリアル

	Vector3 screenVertices_[(int)Vertex::kVertexNum] = {};//スクリーン座標


private://メンバ関数
	/// <summary>
	/// 動き
	/// </summary>
	/// <param name="keys">現在の押しているキー</param>
	/// <param name="preKeys">過去に押しているキー</param>
	void Transfar(char *keys,char *preKeys);
	
};

