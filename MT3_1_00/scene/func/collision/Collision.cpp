#include "Collision.h"
#include "scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/plane/Plane.h"
#include "scene/gameObject/character/line/Line.h"
#include "scene/gameObject/character/triangle/Triangle.h"

// 当たり判定(球と球)
void Collision::IsCollision(Sphere* target, Sphere* sphere) {
	float distance = Math::Length(target->GetSphereMaterial().center - sphere->GetSphereMaterial().center);
	if (distance <= target->GetSphereMaterial().radius + sphere->GetSphereMaterial().radius) {
		target->SetIsHit(true);
	}
	else {
		target->SetIsHit(false);
	}
	target->OnCollision();
}

//当たり判定(球と平面)
void Collision::IsCollision(Sphere* target, Plane* plane) {
	Vector3 normal = plane->GetPlaneMaterial().normal;
	float distance = plane->GetPlaneMaterial().distance;
	float k = fabsf(Math::Dot(normal, target->GetSphereMaterial().center) - distance);
	if (k <= target->GetSphereMaterial().radius) {
		target->SetIsHit(true);
	}
	else {
		target->SetIsHit(false);
	}
	target->OnCollision();//色を変える
}

void Collision::IsCollision(Line* target, Plane* plane) {
	//垂直判定を行うための、法線と線の内積を求める
	float dot = Math::Dot(plane->GetPlaneMaterial().normal, target->GetSegment().diff);

	if (std::abs(dot) < 1e-6f) {
		target->SetIsHit(false);
	}

	float t = (plane->GetPlaneMaterial().distance - Math::Dot(target->GetSegment().origin, plane->GetPlaneMaterial().normal)) / dot;
	if (t >= 0.0f && t <= 1.0f) {
		target->SetIsHit(true);
	}
	else {
		target->SetIsHit(false);
	}
	target->OnCollision();
}

void Collision::IsCollision(Line* target, Triangle* triangle){
	Vector3 v0p = target->GetSegment().origin + target->GetT() * triangle->GetTriangleMaterial().kLocalVertices_[0];
	Vector3 v1p = target->GetSegment().origin + target->GetT() * triangle->GetTriangleMaterial().kLocalVertices_[1];
	Vector3 v2p = target->GetSegment().origin + target->GetT() * triangle->GetTriangleMaterial().kLocalVertices_[2];

	Vector3 v01 = triangle->GetTriangleMaterial().kLocalVertices_[1] - triangle->GetTriangleMaterial().kLocalVertices_[0];
	Vector3 v12 = triangle->GetTriangleMaterial().kLocalVertices_[2] - triangle->GetTriangleMaterial().kLocalVertices_[1];
	Vector3 v20 = triangle->GetTriangleMaterial().kLocalVertices_[0] - triangle->GetTriangleMaterial().kLocalVertices_[2];

	Vector3 normal = Math::Normalize(target->GetSegment().diff);

	Vector3 cross01 = Math::Cross(v01, v1p);
	Vector3 cross12 = Math::Cross(v12, v2p);
	Vector3 cross20 = Math::Cross(v20, v0p);

	if (Math::Dot(cross01, normal) >= 0.0f && Math::Dot(cross12, normal)>=0.0f && Math::Dot(cross20, normal)>=0.0f) {
		target->SetIsHit(true);
	}
	else {
		target->SetIsHit(false);
	}
		target->OnCollision();
}


//template<typename tLine> bool IsCollision(const Triangle& triangle, const tLine& line) {
//	Vector3 v01 = Subtract(triangle.vertices[1], triangle.vertices[0]);
//	Vector3 v12 = Subtract(triangle.vertices[2], triangle.vertices[1]);
//	Vector3 normal = Normalize(Cross(v01, v12));
//	Plane plane{ .normal = normal, .distance = Dot(triangle.vertices[0], normal) };
//	float dot = Dot(plane.normal, line.diff);
//	if (dot == 0.0f) {
//		return false;
//	}
//	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;
//	if ((t < tLine::kTMin) || (tLine::kTMax < t)) {
//		return false;
//	}
//	Vector3 intersect = Add(line.origin, Multiply(t, line.diff));
//	Vector3 v1p = Subtract(intersect, triangle.vertices[1]);
//	if (Dot(Cross(v01, v1p), normal) < 0.0f) {
//		return false;
//	}
//	Vector3 v2p = Subtract(intersect, triangle.vertices[2]);
//	if (Dot(Cross(v12, v2p), normal) < 0.0f) {
//		return false;
//	}
//	Vector3 v0p = Subtract(intersect, triangle.vertices[0]);
//	Vector3 v20 = Subtract(triangle.vertices[0], triangle.vertices[2]);
//	if (Dot(Cross(v20, v0p), normal) < 0.0f) {
//		return false;
//	}
//	return true;
//}