#define NOMINMAX
#include "Collision.h"
#include "scene/gameObject/character/sphere/Sphere.h"
#include "scene/gameObject/character/plane/Plane.h"
#include "scene/gameObject/character/line/Line.h"
#include "scene/gameObject/character/triangle/Triangle.h"
#include "scene/gameObject/character/AABB/AABB.h"
#include "scene/gameObject/character/OBB/OBB.h"
#include "scene/gameObject/character/hexagon/Hexagon.h"
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

// 当たり判定(線と三角形)
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
	return distance <= sphere.radius;
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

// AABBと線分の当たり判定(返り値あり)
bool Collision::IsCollision(const GameObject::AABBMaterial& aabb, const GameObject::Segment& segment) {
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
	return isHit;
}

// OBBと球の当たり判定
void Collision::IsCollision(OBB* target, const GameObject::SphereMaterial& sphere) {
	Vector3 centerInOBBLocalSpace = Math::Transform(sphere.center, target->GetOBBWorldMatrixInvers());
	GameObject::AABBMaterial aabbOBBLocal = { .min = -target->GetSize(),.max = target->GetSize() };
	GameObject::SphereMaterial sphereOBBLocal{ centerInOBBLocalSpace,sphere.radius };
	//ローカル空間で衝突判定
	target->OnCollision(IsCollision(aabbOBBLocal, sphereOBBLocal));
}

// OBBと線分の当たり判定
void Collision::IsCollision(OBB* target, const GameObject::Segment segment) {
	Vector3 localSegmentOrigin = Math::Transform(segment.origin, target->GetOBBWorldMatrixInvers());
	Vector3 localSegmentEnd = Math::Transform(segment.origin + segment.diff, target->GetOBBWorldMatrixInvers());
	GameObject::AABBMaterial localAABB{
		.min = -target->GetSize(),
		.max = target->GetSize(),
	};
	GameObject::Segment localSegment;
	localSegment.origin = localSegmentOrigin;
	localSegment.diff = localSegmentEnd - localSegmentOrigin;
	target->OnCollision(IsCollision(localAABB, localSegment));
}

// OBBとAABB/OBBの当たり判定
void Collision::IsCollision(OBB* target, OBB* obb) {
	//分割軸の数
	Vector3 separateAxes[15];
	//面の法線
	/*ターゲット*/
	separateAxes[0] = target->GetOBBMaterial().orientations[0];
	separateAxes[1] = target->GetOBBMaterial().orientations[1];
	separateAxes[2] = target->GetOBBMaterial().orientations[2];
	/*ターゲットではないほう*/
	separateAxes[3] = obb->GetOBBMaterial().orientations[0];
	separateAxes[4] = obb->GetOBBMaterial().orientations[1];
	separateAxes[5] = obb->GetOBBMaterial().orientations[2];
	//9つの辺のクロス積
	separateAxes[6] = Math::Cross(target->GetOBBMaterial().orientations[0], obb->GetOBBMaterial().orientations[0]);
	separateAxes[7] = Math::Cross(target->GetOBBMaterial().orientations[0], obb->GetOBBMaterial().orientations[1]);
	separateAxes[8] = Math::Cross(target->GetOBBMaterial().orientations[0], obb->GetOBBMaterial().orientations[2]);
	separateAxes[9] = Math::Cross(target->GetOBBMaterial().orientations[1], obb->GetOBBMaterial().orientations[0]);
	separateAxes[10] = Math::Cross(target->GetOBBMaterial().orientations[1], obb->GetOBBMaterial().orientations[1]);
	separateAxes[11] = Math::Cross(target->GetOBBMaterial().orientations[1], obb->GetOBBMaterial().orientations[2]);
	separateAxes[12] = Math::Cross(target->GetOBBMaterial().orientations[2], obb->GetOBBMaterial().orientations[0]);
	separateAxes[13] = Math::Cross(target->GetOBBMaterial().orientations[2], obb->GetOBBMaterial().orientations[1]);
	separateAxes[14] = Math::Cross(target->GetOBBMaterial().orientations[2], obb->GetOBBMaterial().orientations[2]);

	//半分のベクトル
	/*ターゲット*/
	Vector3 targetDirection[3]{
		target->GetOBBMaterial().orientations[0] * target->GetOBBMaterial().size.x,
		target->GetOBBMaterial().orientations[1] * target->GetOBBMaterial().size.y,
		target->GetOBBMaterial().orientations[2] * target->GetOBBMaterial().size.z,
	};
	/*OBB*/
	Vector3 obbDirection[3]{
		obb->GetOBBMaterial().orientations[0] * obb->GetOBBMaterial().size.x,
		obb->GetOBBMaterial().orientations[1] * obb->GetOBBMaterial().size.y,
		obb->GetOBBMaterial().orientations[2] * obb->GetOBBMaterial().size.z,
	};

	//頂点の数
	const int kCornerNum = 8;

	// 点(頂点)
	Vector3 targetCorners[kCornerNum] = {
	  target->GetOBBMaterial().center + targetDirection[0] + targetDirection[1] + targetDirection[2],//背面の右上
	  target->GetOBBMaterial().center + targetDirection[0] + targetDirection[1] - targetDirection[2],//正面の右上
	  target->GetOBBMaterial().center + targetDirection[0] - targetDirection[1] + targetDirection[2],//背面の右下
	  target->GetOBBMaterial().center + targetDirection[0] - targetDirection[1] - targetDirection[2],//正面の右下
	  target->GetOBBMaterial().center - targetDirection[0] + targetDirection[1] + targetDirection[2],//背面の左上
	  target->GetOBBMaterial().center - targetDirection[0] + targetDirection[1] - targetDirection[2],//正面の左上
	  target->GetOBBMaterial().center - targetDirection[0] - targetDirection[1] + targetDirection[2],//背面の左下
	  target->GetOBBMaterial().center - targetDirection[0] - targetDirection[1] - targetDirection[2],//正面の左下
	};
	Vector3 obbCorners[kCornerNum] = {
	 obb->GetOBBMaterial().center + obbDirection[0] + obbDirection[1] + obbDirection[2],//背面の右上
	 obb->GetOBBMaterial().center + obbDirection[0] + obbDirection[1] - obbDirection[2],//正面の右上
	 obb->GetOBBMaterial().center + obbDirection[0] - obbDirection[1] + obbDirection[2],//背面の右下
	 obb->GetOBBMaterial().center + obbDirection[0] - obbDirection[1] - obbDirection[2],//正面の右下
	 obb->GetOBBMaterial().center - obbDirection[0] + obbDirection[1] + obbDirection[2],//背面の左上
	 obb->GetOBBMaterial().center - obbDirection[0] + obbDirection[1] - obbDirection[2],//正面の左上
	 obb->GetOBBMaterial().center - obbDirection[0] - obbDirection[1] + obbDirection[2],//背面の左下
	 obb->GetOBBMaterial().center - obbDirection[0] - obbDirection[1] - obbDirection[2],//正面の左下
	};
	// 中心点間のベクトル
	Vector3 centerToCenter = target->GetOBBMaterial().center - obb->GetOBBMaterial().center;

	//当たったかの判定
	bool isHit = true;

	//当たり判定の計算
	for (const auto& separateAxis : separateAxes) {
		float minTarget = (numeric_limits<float>::max)();
		float maxTarget = (numeric_limits<float>::lowest)();
		float minOBB = minTarget;
		float maxOBB = maxTarget;
		for (auto cornerIndex = 0; cornerIndex < kCornerNum; cornerIndex++) {
			float targetDistance = Math::Dot(targetCorners[cornerIndex], separateAxis);
			minTarget = (min)(targetDistance, minTarget);
			maxTarget = (max)(targetDistance, maxTarget);
			float obbDistance = Math::Dot(obbCorners[cornerIndex], separateAxis);
			minOBB = (min)(obbDistance, minOBB);
			maxOBB = (max)(obbDistance, maxOBB);
		}
		//それぞれを射影した範囲長の合計を求める
		float sumSpan = maxTarget - minTarget + maxOBB - minOBB;
		//最大範囲を求める
		float longSpan = (max)(maxTarget, maxOBB) - (min)(minTarget, minOBB);
		//分離軸が見つかる判定
		if (sumSpan < longSpan) {
			isHit = false;
		}
	}
	//ターゲットの当たり判定を実行
	target->OnCollision(isHit);
}


bool Collision::IsCollision(Hexagon* hexagon, Line* line) {
	// 六角形の各辺
	Vector3 edge[6]{
		hexagon->GetVertex()[1] - hexagon->GetVertex()[0],
		hexagon->GetVertex()[2] - hexagon->GetVertex()[1],
		hexagon->GetVertex()[3] - hexagon->GetVertex()[2],
		hexagon->GetVertex()[4] - hexagon->GetVertex()[3],
		hexagon->GetVertex()[5] - hexagon->GetVertex()[4],
		hexagon->GetVertex()[0] - hexagon->GetVertex()[5],
	};

	//衝突したかどうか
	bool isHit = false;

	//六角形の面の法線
	Vector3 normal = Math::Normalize(Math::Cross(edge[0], edge[1]));


	//疑似的に平面を作成
	GameObject::PlaneMaterial plane = { .normal = normal,.distance = Math::Dot(hexagon->GetVertex()[0],normal) };

	//平面の法線とラインの差分が向き合っているかどうか
	float dot = Math::Dot(plane.normal, line->GetSegment().diff);

	//平行だったらtrueを返す
	if (std::abs(dot) < 1e-6f) {
		isHit = false;
	}

	//平面を求める
	float t = (plane.distance - Math::Dot(line->GetSegment().origin, plane.normal)) / dot;

	//六角形の各辺に重なっているかの計算
	Vector3 intersect = line->GetSegment().origin + t * line->GetSegment().diff;
	Vector3 v0p = intersect - hexagon->GetVertex()[0];
	Vector3 v1p = intersect - hexagon->GetVertex()[1];
	Vector3 v2p = intersect - hexagon->GetVertex()[2];
	Vector3 v3p = intersect - hexagon->GetVertex()[3];
	Vector3 v4p = intersect - hexagon->GetVertex()[4];
	Vector3 v5p = intersect - hexagon->GetVertex()[5];

	
	//平面の中にある六角形に線が当たっているかの判定
	if (t >= kTMin && t <= kTMax) {

		if (Math::Dot(Math::Cross(edge[0], v0p), normal) < 0.0f) {
			isHit = false;
		}
		else if (Math::Dot(Math::Cross(edge[1], v1p), normal) < 0.0f) {
			isHit = false;
		}
		else if (Math::Dot(Math::Cross(edge[2], v2p), normal) < 0.0f) {
			isHit = false;
		}
		else if (Math::Dot(Math::Cross(edge[3], v3p), normal) < 0.0f) {
			isHit = false;
		}
		else if (Math::Dot(Math::Cross(edge[4], v4p), normal) < 0.0f) {
			isHit = false;
		}
		else if (Math::Dot(Math::Cross(edge[5], v5p), normal) < 0.0f) {
			isHit = false;
		}
		else {
			isHit = true;
		}
	}

	return isHit;
}

























