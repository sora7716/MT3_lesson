#include "Collision.h"
#include "scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/plane/Plane.h"
#include "scene/gameObject/character/point/Point.h"

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
	ImGui::Text("k%f", k);
}

void Collision::IsCollision(Point* target, Plane* plane) {
	//垂直判定を行うための、法線と線の内積を求める
	float dot = Math::Dot(plane->GetPlaneMaterial().normal, target->GetSegment().diff);

	if (std::abs(dot) == 1e-6f) {
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
	ImGui::Text("%f", t);
}
