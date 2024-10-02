#define NOMINMAX
#include "Collision.h"
#include "scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/plane/Plane.h"
#include "scene/gameObject/character/line/Line.h"
#include "scene/gameObject/character/triangle/Triangle.h"
#include "scene/gameObject/character/AABB/AABB.h"
#include "scene/gameObject/character/OBB/OBB.h"
#include <algorithm> 
using namespace std;

// 当たり判定(球と球)
void Collision::IsCollision(Sphere* target, const GameObject::SphereMaterial& sphere1, const GameObject::SphereMaterial& sphere2) {
	float distance = Math::Length(sphere1.center - sphere2.center);
	if (distance <= sphere1.radius + sphere2.radius) {
		target->SetIsHit(true);
	}
	else {
		target->SetIsHit(false);
	}
	target->OnCollision();
}

//当たり判定(球と平面)
void Collision::IsCollision(Sphere* target, const GameObject::SphereMaterial& sphere, const GameObject::PlaneMaterial& plane) {
	Vector3 normal = plane.normal;
	float distance = plane.distance;
	float k = fabsf(Math::Dot(normal, sphere.center) - distance);
	if (k <= sphere.radius) {
		target->SetIsHit(true);
	}
	else {
		target->SetIsHit(false);
	}
	target->OnCollision();//色を変える
}

//当たり判定(線と平面)
void Collision::IsCollision(Line* target, const GameObject::Segment& segment, const GameObject::PlaneMaterial& plane) {
	//垂直判定を行うための、法線と線の内積を求める
	float dot = Math::Dot(plane.normal, segment.diff);
	if (std::abs(dot) < 1e-6f) {
		target->SetIsHit(false);
	}

	float t = (plane.distance - Math::Dot(segment.origin, plane.normal)) / dot;
	if (t >= 0.0f && t <= 1.0f) {
		target->SetIsHit(true);
	}
	else {
		target->SetIsHit(false);
	}
	target->OnCollision();
}

//AABBの当たり判定
void Collision::IsCollision(Line* target, const GameObject::Segment& segment, const GameObject::TriangleMaterial& triangle) {

	Vector3 v01 = triangle.kLocalVertices_[1] - triangle.kLocalVertices_[0];
	Vector3 v12 = triangle.kLocalVertices_[2] - triangle.kLocalVertices_[1];

	Vector3 normal = Math::Normalize(Math::Cross(v01, v12));
	float dot = Math::Dot(normal, segment.diff);
	float distance = Math::Dot(triangle.kLocalVertices_[0], normal);
	float t = (distance - Math::Dot(segment.origin, normal)) / dot;

	Vector3 intersect = segment.origin + t * segment.diff;
	Vector3 v1p = intersect - triangle.kLocalVertices_[1];
	Vector3 v2p = intersect - triangle.kLocalVertices_[2];
	Vector3 v0p = intersect - triangle.kLocalVertices_[0];
	Vector3 v20 = triangle.kLocalVertices_[0] - triangle.kLocalVertices_[2];

	if (std::abs(dot) < 1e-6f) {
		target->SetIsHit(false);
	}
	if (t >= kTMin && t <= kTMax) {
		target->SetIsHit(true);
	}

	if (Math::Dot(Math::Cross(v01, v1p), normal) < 0.0f) {
		target->SetIsHit(false);
	}
	else if (Math::Dot(Math::Cross(v12, v2p), normal) < 0.0f) {
		target->SetIsHit(false);
	}
	else if (Math::Dot(Math::Cross(v20, v0p), normal) < 0.0f) {
		target->SetIsHit(false);
	}
	else {
		target->SetIsHit(true);
	}
	target->OnCollision();
}

//AABBの当たり判定
void Collision::IsCollision(AABB* target, GameObject::AABBMaterial aabb1, GameObject::AABBMaterial aabb2) {
	//X座標の当たってない判定
	if (aabb1.min.x < aabb2.max.x && aabb1.max.x < aabb2.min.x) {
		target->SetIsHit(false);
	}
	else if (aabb2.max.x < aabb1.min.x && aabb2.min.x < aabb1.max.x) {
		target->SetIsHit(false);
	}

	// Y座標の当たってない判定
	else if (aabb1.max.y > aabb2.min.y && aabb1.min.y > aabb2.max.y) {
		target->SetIsHit(false);
	}
	else if (aabb2.max.y > aabb1.min.y && aabb2.min.y > aabb1.max.y) {
		target->SetIsHit(false);
	}

	// Z座標の当たってない判定
	else if (aabb1.min.z < aabb2.max.z && aabb1.max.z < aabb2.min.z) {
		target->SetIsHit(false);
	}
	else if (aabb2.max.z < aabb1.min.z && aabb2.min.z < aabb1.max.z) {
		target->SetIsHit(false);
	}

	else {
		target->SetIsHit(true);
	}
	target->OnCollision();
}

//ボックスと球の当たり判定
void Collision::IsCollision(AABB* target, const GameObject::AABBMaterial& aabb, const GameObject::SphereMaterial& sphere) {
	Vector3 closestPoint = {
		clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		clamp(sphere.center.y,aabb.min.y,aabb.max.y),
		clamp(sphere.center.z,aabb.min.z,aabb.max.z),
	};
	//最近接点と球の中心との距離を求める
	float distance = Math::Length(closestPoint - sphere.center);
	//球の半径より上記の距離が小さかったら衝突
	if (distance <= sphere.radius) {
		target->SetIsHit(true);
	}
	else {
		target->SetIsHit(false);
	}
	target->OnCollision();
}

// AABBと球の当たり判定
bool Collision::IsCollision(GameObject::AABBMaterial& aabb, const GameObject::SphereMaterial& sphere) {
	Vector3 closestPoint = {
		clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		clamp(sphere.center.y,aabb.min.y,aabb.max.y),
		clamp(sphere.center.z,aabb.min.z,aabb.max.z),
	};
	//最近接点と球の中心との距離を求める
	float distance = Math::Length(closestPoint - sphere.center);
	//球の半径より上記の距離が小さかったら衝突
	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}

//ボックスと線分の当たり判定
void Collision::IsCollision(AABB* target, const GameObject::AABBMaterial& aabb, const GameObject::Segment& segment) {
	GameObject::AABBMaterial t;
	Vector3 tNear;
	Vector3 tFar;


	t.min.x = (aabb.min.x - segment.origin.x) / segment.diff.x;
	t.max.x = (aabb.max.x - segment.origin.x) / segment.diff.x;

	t.min.y = (aabb.min.y - segment.origin.y) / segment.diff.y;
	t.max.y = (aabb.max.y - segment.origin.y) / segment.diff.y;

	t.min.z = (aabb.min.z - segment.origin.z) / segment.diff.z;
	t.max.z = (aabb.max.z - segment.origin.z) / segment.diff.z;

	tNear.x = min(t.min.x, t.max.x);
	tFar.x = max(t.min.x, t.max.x);

	tNear.y = min(t.min.y, t.max.y);
	tFar.y = max(t.min.y, t.max.y);

	tNear.z = min(t.min.z, t.max.z);
	tFar.z = max(t.min.z, t.max.z);

	float tMin = max(tNear.x, max(tNear.z, tNear.y));
	float tMax = min(tFar.x, min(tFar.z, tFar.y));
	bool isHit = false;
	if (tMin <= tMax) {
		if (tMin * tMax < 0.0f) {
			isHit = true;
		}
		if (kTMin <= tMin && tMin <= kTMax || kTMin <= tMax && tMax <= kTMax) {
			isHit = true;
		}
	}
	else {
		isHit = false;
	}
	target->SetIsHit(isHit);
	target->OnCollision();
}

// OBBと球の当たり判定
void Collision::IsCollision(OBB* target, const Matrix4x4& obbWorldMatrixInvers, const GameObject::SphereMaterial& sphere) {
	Vector3 centerInOBBLocalSpace = Math::Transform(sphere.center, obbWorldMatrixInvers);
	GameObject::AABBMaterial aabbOBBLocal = { .min = -target->GetSize(),.max = target->GetSize() };
	GameObject::SphereMaterial sphereOBBLocal{ centerInOBBLocalSpace,sphere.radius };
	//ローカル空間で衝突判定
	target->OnCollision(IsCollision(aabbOBBLocal, sphereOBBLocal));
}




























