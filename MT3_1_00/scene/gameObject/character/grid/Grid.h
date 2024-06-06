#pragma once
#include "scene/gameObject/character/Character.h"

//前方宣言
class Camera;

class Grid :public Character{

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Initialize(Camera *camera);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private:
	Camera* camera_ = nullptr;//カメラ
	Vector3 start_[11] = {};
	Vector3 end_[11] = {};
	MyVector3 ndcVertexStart_[11] = {};
	MyVector3 ndcVertexEnd_[11] = {};
	MyVector3 screenStart_[11] ={};
	MyVector3 screenEnd_[11] ={};
	
};

