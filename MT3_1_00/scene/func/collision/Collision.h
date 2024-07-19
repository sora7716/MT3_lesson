#pragma once
#include <Vector3.h>
#include "scene/gameObject/GameObject.h"

//前方宣言
class Sphere;
class Plane;
class Line;
class Triangle;
class AABB;

class Collision {

public://メンバ関数

	/// <summary>
	///  当たり判定(球と球)
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="sphere1">球1</param>
	/// <param name="sphere2">球2</param>
	void IsCollision(Sphere* target, const GameObject::SphereMaterial& sphere1, const GameObject::SphereMaterial& sphere2);

	/// <summary>
	///  当たり判定(球と平面)
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	void IsCollision(Sphere* target, const GameObject::SphereMaterial& sphere, const GameObject::PlaneMaterial& plane);

	/// <summary>
	/// 当たり判定(線と平面)
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="segment">線分</param>
	/// <param name="plane">平面</param>
	void IsCollision(Line* target, const GameObject::Segment& segment, const GameObject::PlaneMaterial& plane);

	/// <summary>
	/// 当たり判定(線と三角形)
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="segment">線分</param>
	/// <param name="triangle">三角形</param>
	void IsCollision(Line* target, const GameObject::Segment& segment, const GameObject::TriangleMaterial& triangle);

	/// <summary>
	/// AABBの当たり判定
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="aabb1">ボックス1</param>
	/// <param name="aabb2">ボックス2</param>
	void IsCollision(AABB* target, GameObject::AABBMaterial aabb1, GameObject::AABBMaterial aabb2);

	/// <summary>
	/// ボックスと球の当たり判定
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="aabb">ボックス</param>
	/// <param name="sphere">球</param>
	void IsCollision(AABB* target, const GameObject::AABBMaterial& aabb, const GameObject::SphereMaterial& sphere);
};

