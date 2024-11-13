
#pragma once
#include "scene/gameObject/character/Character.h"
class Triangle :public Character {
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Triangle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Triangle() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="triangleMaterial"></param>
	void Initialize(Camera* camera, TriangleMaterial&& triangleMaterial);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="label"></param>
	void DebugText(const char* label);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ローカルの頂点
	/// </summary>
	/// <param name="i">正面か背面か</param>
	/// <returns>頂点</returns>
	Vector3* GetLocalVertex(int i);

	/// <summary>
	/// 三角柱のゲッター
	/// </summary>
	/// <returns></returns>
	TriangleMaterial GetTriangleMaterial();

private://メンバ関数

	/// <summary>
	/// 法線ベクトルの作成
	/// </summary>
	void CreateNormal();

public://静的メンバ変数
	static inline const int kVertexNum = static_cast<int>(GameObject::Vertex::kVertexNum);
private://メンバ変数
	//カメラ
	Camera* camera_ = nullptr;
	TriangleMaterial triangle_ = {};
	Vector3 localVertex_[2][kVertexNum];
	Vector3 screenVertex_[2][kVertexNum];
};
