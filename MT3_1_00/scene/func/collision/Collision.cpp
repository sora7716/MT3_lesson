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

void Collision::IsCollision(Line* target, Triangle* triangle) {
	
	Vector3 v01 = triangle->GetTriangleMaterial().kLocalVertices_[1] - triangle->GetTriangleMaterial().kLocalVertices_[0];
	Vector3 v12 = triangle->GetTriangleMaterial().kLocalVertices_[2] - triangle->GetTriangleMaterial().kLocalVertices_[1];
	
	Vector3 normal = Math::Normalize(Math::Cross(v01, v12));
	float dot = Math::Dot(normal, target->GetSegment().diff);
	float distance = Math::Dot(triangle->GetTriangleMaterial().kLocalVertices_[0], normal);
	float t = (distance - Math::Dot(target->GetSegment().origin, normal)) / dot;

	Vector3 intersect = target->GetSegment().origin + t * target->GetSegment().diff;
	Vector3 v1p = intersect - triangle->GetTriangleMaterial().kLocalVertices_[1];
	Vector3 v2p = intersect - triangle->GetTriangleMaterial().kLocalVertices_[2];
	Vector3 v0p = intersect - triangle->GetTriangleMaterial().kLocalVertices_[0];
	Vector3 v20 = triangle->GetTriangleMaterial().kLocalVertices_[0] - triangle->GetTriangleMaterial().kLocalVertices_[2];

	/*if (std::abs(dot) < 1e+6f) {
		target->SetIsHit(false);
	}
	if (t >= 0.0f && t <= 1.0f) {
		target->SetIsHit(true);
	}*/

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


//template<typename tLine> bool IsCollision(const Triangle& triangle, const tLine& line) {
	//Vector3 v01 = triangle->GetTriangleMaterial().kLocalVertices_[1] - triangle->GetTriangleMaterial().kLocalVertices_[0];
	//Vector3 v12 = triangle->GetTriangleMaterial().kLocalVertices_[2] - triangle->GetTriangleMaterial().kLocalVertices_[1];
	//Vector3 normal = Math::Normalize(Math::Cross(v01, v12));
	//Plane* plane = new Plane();
	//plane->SetPlane({ normal,Math::Dot(triangle->GetTriangleMaterial().kLocalVertices_[0], normal) });
	//float dot = Math::Dot(plane->GetPlaneMaterial().normal, target->GetSegment().diff);
	/*if (dot == 0.0f) {
		target->SetIsHit(false);
	}
	else {
		target->SetIsHit(true);
	}*/
	//float t = (plane->GetPlaneMaterial().distance - Math::Dot(target->GetSegment().origin, plane->GetPlaneMaterial().normal)) / dot;
		/*if ((t < 0.0f) || (1.0f < t)) {
			target->SetIsHit(false);
		}
		else {
			target->SetIsHit(true);
		}*/
//Vector3 intersect = target->GetSegment().origin + t * target->GetSegment().diff;
//Vector3 v1p = intersect - triangle->GetTriangleMaterial().kLocalVertices_[1];
//if (Math::Dot(Math::Cross(v01, v1p), normal) < 0.0f) {
//	target->SetIsHit(false);
//}
//else {
//	target->SetIsHit(true);
//}

/*Vector3 v2p = intersect - triangle->GetTriangleMaterial().kLocalVertices_[2];
	if (Math::Dot(Math::Cross(v12, v2p), normal) < 0.0f) {
		target->SetIsHit(false);
	}
	else {
		target->SetIsHit(true);
	}*/
	/*Vector3 v0p = intersect - triangle->GetTriangleMaterial().kLocalVertices_[0];
		Vector3 v20 = triangle->GetTriangleMaterial().kLocalVertices_[0] - triangle->GetTriangleMaterial().kLocalVertices_[2];
		if (Math::Dot(Math::Cross(v20, v0p), normal) < 0.0f) {
			target->SetIsHit(false);
		}
		else {
			target->SetIsHit(true);
		}

		target->OnCollision();*/

























