#pragma once
#include "scene/gameObject/character/Character.h"

//前方宣言
class Camera;

class Grid :public Character {

public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Initialize(Camera* camera);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private://メンバ変数

	static inline const uint32_t kElementCount = 11;//線の要素数

	Camera* camera_ = nullptr;//カメラ
	//線の始点↓
	Vector3 localStart_[kElementCount] = {};  //位置
	Vector3 ndcVertexStart_[kElementCount] = {};//正規化デバイス座標
	Vector3 screenStart_[kElementCount] = {};//スクリーン座標
	//線の始点↑

	//線の終点↓
	Vector3 locakEnd_[kElementCount] = {};    //位置
	Vector3 ndcVertexEnd_[kElementCount] = {};//正規化デバイス座標
	Vector3 screenEnd_[kElementCount] = {};//スクリーン座標
	//線の終点↑

	uint32_t color = 0xFFFFFFFF;//線の色

};

