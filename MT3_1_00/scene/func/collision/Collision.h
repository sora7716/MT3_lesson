#pragma once
#include <Vector3.h>

//前方宣言
class Sphere;
class Plane;
class Point;

class Collision {

public://メンバ関数
	/// <summary>
	///  当たり判定(球と球)
	/// </summary>
	/// <param name="target">当たり判定をしたい対象</param>
	/// <param name="sphere">球</param>
	void IsCollision(Sphere* target, Sphere* sphere);

    /// <summary>
    /// 当たり判定(球と平面)
    /// </summary>
    /// <param name="target">当たり判定をしたい対象</param>
    /// <param name="plane">平面</param>
    void IsCollision(Sphere*target,Plane* plane);

	/// <summary>
	/// 当たり判定(線と平面)
	/// </summary>
	/// <param name="target"></param>
	/// <param name="plane"></param>
	void IsCollision(Point* target, Plane* plane);
};

