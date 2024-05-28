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
	/// <param name="keys">keys</param>
	/// <param name="preKeys">preKeys</param>
	void Update(char *keys,char *preKeys);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private://メンバ変数

	Camera* camera_ = nullptr;

	MyVector3 v1_    = {};//ベクトル1
	MyVector3 v2_    = {};//ベクトル2
	MyVector3 cross_ = {};//クロス積
	
	MyVector3 normalize_ = {};
	MyVector3 viewVector_ = {};
	float disappear_ = 0;
};

