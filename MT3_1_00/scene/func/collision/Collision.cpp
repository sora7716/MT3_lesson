#include "Collision.h"
#include "scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/plane/Plane.h"

// 当たり判定(球と球)
void Collision::IsCollision(Sphere* target,Sphere* sphere){
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
void Collision::IsCollision(Sphere* target, Plane* plane){
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
