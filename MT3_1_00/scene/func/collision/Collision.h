#pragma once
#include <Vector3.h>
#include "scene/gameObject/GameObject.h"

//前方宣言
class Sphere;
class Plane;
class Line;
class Triangle;
class AABB;
class OBB;
class Hexagon;

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
	/// <param name="aabb1">AABB1</param>
	/// <param name="aabb2">AABB2</param>
	void IsCollision(AABB* target, GameObject::AABBMaterial aabb1, GameObject::AABBMaterial aabb2);

	/// <summary>
	/// AABBと球の当たり判定
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="aabb">AABB</param>
	/// <param name="sphere">球</param>
	void IsCollision(AABB* target, const GameObject::AABBMaterial& aabb, const GameObject::SphereMaterial& sphere);

	/// <summary>
	/// AABBと球の当たり判定(返り値あり)
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="sphere">球</param>
	/// <returns>当たり判定</returns>
	bool IsCollision(GameObject::AABBMaterial& aabb, const GameObject::SphereMaterial& sphere);

	/// <summary>
	/// AABBと線分の当たり判定
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="aabb">AABB</param>
	void IsCollision(AABB* target, const GameObject::AABBMaterial& aabb, const GameObject::Segment& segment);

	/// <summary>
	/// AABBと線分の当たり判定(返り値あり)
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="segment">線分</param>
	/// <returns>当たり判定</returns>
	bool IsCollision(const GameObject::AABBMaterial& aabb, const GameObject::Segment& segment);

	/// <summary>
	/// OBBと球の当たり判定
	/// </summary>
    /// <param name="target">ターゲット</param>
	/// <param name="sphare">球</param>
	void IsCollision(OBB* target,const GameObject::SphereMaterial& sphere);

	/// <summary>
	/// OBBと線分の当たり判定
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="segment">線分</param>
	void IsCollision(OBB* target, const GameObject::Segment segment);

	/// <summary>
	/// OBBとAABB/OBBの当たり判定
	/// </summary>
	/// <param name="target">ターゲット</param>
	/// <param name="obb">OBB</param>
	void IsCollision(OBB* target, OBB* obb);

	/// <summary>
	/// 六角形と線の当たり判定
	/// </summary>
	/// <param name="hexagon">六角形</param>
	/// <param name="line">線分</param>
	/// <returns>衝突したか</returns>
	bool IsCollision(Hexagon*hexagon,Line*line);

public://静的メンバ変数
	static inline const float kTMin = 0.0f;
	static inline const float kTMax = 1.0f;
};

