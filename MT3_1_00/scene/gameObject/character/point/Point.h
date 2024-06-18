#pragma once
#include "scene/gameObject/character/Character.h"

//前方宣言
class Camera;

class Point:public Character{
public://メンバ関数

	//直線
	typedef struct StraightLine {
		Vector3 origin;//始点
		Vector3 diff;//終点への差分ベクトル
	}StraightLine;

	//半直線
	typedef struct Ray {
		Vector3 origin;//始点
		Vector3 diff; //終点への差分ベクトル
	}Ray;

	//線分
	typedef struct Segment {
		Vector3 origin;//始点
		Vector3 diff; //終点への差分ベクトル
	}Segment;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Point();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Point();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Camera*camera);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 最近接点のゲッター
	/// </summary>
	/// <returns>最近接点</returns>
	Vector3 GetClosestPoint();

	/// <summary>
	/// 原点のセッター
	/// </summary>
	/// <returns>原点</returns>
	Vector3 GetPoint();

	/// <summary>
	/// 原点のセッター
	/// </summary>
	/// <param name="point">セットしたい値</param>
	void SetPoint(const Vector3& point);
	
	/// <summary>
	/// 線分のセッター
	/// </summary>
	/// <param name="segment">セットしたい値</param>
	void SetSegment(const Segment& segment);

private://メンバ関数
	
	/// <summary>
	/// 正射影ベクトル
	/// </summary>
	/// <param name="v1">ベクトル1</param>
	/// <param name="v2">ベクトル2</param>
	void Project(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 最近接点
	/// </summary>
	/// <param name="point">原点</param>
	/// <param name="segment">線分</param>
	void ClosestPoint();

private://メンバ変数
	float t_;//媒介変数表示
	Vector3 project_;//正射影ベクトル
	Vector3 closestPoint_;//最近接点
	Vector3 point_;//原点
	Segment segment_;//線分
	Camera* camera_;//カメラ
};

