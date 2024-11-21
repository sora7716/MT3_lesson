#pragma once
#include "scene/gameObject/character/Character.h"

//前方宣言
class Camera;

class Grid :public Character {

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Grid();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Grid();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Initialize(Camera* camera);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(char* keys, char* preKeys);

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText(int i);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private://静的メンバ変数
	static inline const uint32_t kSubdivision = 30;
	static inline const float kRotateSpeed = 0.05f;//回転スピード

public://静的メンバ変数
	static inline const uint32_t kElementCount = kSubdivision + 1;//線の要素

private://メンバ変数

	Camera* camera_;//カメラ
	Vector3 gridScale_[kElementCount];
	Vector3 gridRotate_[kElementCount];
	Vector3 gridTranslate_[kElementCount];
	//線の始点↓
	Vector3 localStart_[kElementCount];  //位置
	Vector3 ndcVertexStart_[kElementCount];//正規化デバイス座標
	Vector3 screenStart_[kElementCount];//スクリーン座標
	//線の始点↑

	//線の終点↓
	Vector3 locakEnd_[kElementCount];    //位置
	Vector3 ndcVertexEnd_[kElementCount];//正規化デバイス座標
	Vector3 screenEnd_[kElementCount];//スクリーン座標
	//線の終点↑

	uint32_t color;//線の色
	Vector3 rotateSpeed_;//回転スピード
};

