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
	const int kObjectNum = 2;//オブジェクトの数
	const int kDirectionNum = 3;//面の法線の数
	const int kVertexNum = 8;//頂点の数
	const int kEdgeNum = kVertexNum / 2;//辺の数

	//9つの辺のクロス積
	Vector3 cross[9];
	cross[0] = Math::Cross(target->GetOBBMaterial().orientations[0], obb->GetOBBMaterial().orientations[0]);
	cross[1] = Math::Cross(target->GetOBBMaterial().orientations[0], obb->GetOBBMaterial().orientations[1]);
	cross[2] = Math::Cross(target->GetOBBMaterial().orientations[0], obb->GetOBBMaterial().orientations[2]);
	cross[3] = Math::Cross(target->GetOBBMaterial().orientations[1], obb->GetOBBMaterial().orientations[0]);
	cross[4] = Math::Cross(target->GetOBBMaterial().orientations[1], obb->GetOBBMaterial().orientations[1]);
	cross[5] = Math::Cross(target->GetOBBMaterial().orientations[1], obb->GetOBBMaterial().orientations[2]);
	cross[6] = Math::Cross(target->GetOBBMaterial().orientations[2], obb->GetOBBMaterial().orientations[0]);
	cross[7] = Math::Cross(target->GetOBBMaterial().orientations[2], obb->GetOBBMaterial().orientations[1]);
	cross[8] = Math::Cross(target->GetOBBMaterial().orientations[2], obb->GetOBBMaterial().orientations[2]);

	//すべての頂点に射影[オブジェクトの数][座標の数][頂点の数]
	static Vector3 project[kObjectNum][kDirectionNum][kVertexNum];//射影した位置
	static GameObject::Vertex2D tempVertex[kObjectNum]{};//頂点位置を格納する仮の場所
	static Vector3 tempOrientations[kDirectionNum]{};//面の法線を格納する仮の場所
	const int kVertexType = 2;//頂点が正面にあるのか背面にあるのかのタイプ
	for (int i = 0; i < kObjectNum; i++) {
		//ターゲットの頂点と面の法線ベクトルを保存してる
		if (i == 0) {
			//頂点
			for (int j = 0; j < kVertexType; j++) {
				tempVertex[j] = target->GetLocalVertex()[j];
			}
			//法線ベクトル
			for (int j = 0; j < 3; j++) {
				tempOrientations[j] = target->GetOBBMaterial().orientations[j];
			}
		}
		//ターゲット以外のOBBの頂点と法線ベクトルを保存してる
		else {
			//頂点
			for (int j = 0; j < kVertexType; j++) {
				tempVertex[j] = obb->GetLocalVertex()[j];
			}
			//法線ベクトル
			for (int j = 0; j < 3; j++) {
				tempOrientations[j] = obb->GetOBBMaterial().orientations[j];
			}
		}
		//射影ベクトルを求める
		for (int j = 0; j < kDirectionNum; j++) {
			project[i][j][0] = Math::Project(tempVertex[0].leftTop,     tempOrientations[j]);
			project[i][j][1] = Math::Project(tempVertex[0].leftBottom,  tempOrientations[j]);
			project[i][j][2] = Math::Project(tempVertex[0].rightTop,    tempOrientations[j]);
			project[i][j][3] = Math::Project(tempVertex[0].rightBottom, tempOrientations[j]);
			project[i][j][4] = Math::Project(tempVertex[1].leftTop,     tempOrientations[j]);
			project[i][j][5] = Math::Project(tempVertex[1].leftBottom,  tempOrientations[j]);
			project[i][j][6] = Math::Project(tempVertex[1].rightTop,    tempOrientations[j]);
			project[i][j][7] = Math::Project(tempVertex[1].rightBottom, tempOrientations[j]);
		}
	};

	//射影した点の最大値と最小値を求める
	//0,3
	//1,2
	//4,7
	//5,6
	static Vector3 minPos[kObjectNum][kEdgeNum]{};//最大値
	static Vector3 maxPos[kObjectNum][kEdgeNum]{};//最小値
	for (int i = 0; i < kObjectNum; i++) {
		for (int j = 0; j < kDirectionNum; j++) {
			//X
			minPos[i][j].x = std::min({ project[i][j][0].x, project[i][j][1].x, project[i][j][2].x, project[i][j][3].x, project[i][j][4].x, project[i][j][5].x, project[i][j][6].x, project[i][j][7].x });
			maxPos[i][j].x = std::max({ project[i][j][0].x, project[i][j][1].x, project[i][j][2].x, project[i][j][3].x, project[i][j][4].x, project[i][j][5].x, project[i][j][6].x, project[i][j][7].x });

			//Y
			minPos[i][j].y = std::min({ project[i][j][0].y, project[i][j][1].y, project[i][j][2].y, project[i][j][3].y, project[i][j][4].y, project[i][j][5].y, project[i][j][6].y, project[i][j][7].y });
			maxPos[i][j].y = std::max({ project[i][j][0].y, project[i][j][1].y, project[i][j][2].y, project[i][j][3].y, project[i][j][4].y, project[i][j][5].y, project[i][j][6].y, project[i][j][7].y });

			//Z
			minPos[i][j].z = std::min({ project[i][j][0].z, project[i][j][1].z, project[i][j][2].z, project[i][j][3].z, project[i][j][4].z, project[i][j][5].z, project[i][j][6].z, project[i][j][7].z });
			maxPos[i][j].z = std::max({ project[i][j][0].z, project[i][j][1].z, project[i][j][2].z, project[i][j][3].z, project[i][j][4].z, project[i][j][5].z, project[i][j][6].z, project[i][j][7].z });
		}
	}

	//分割軸の長さを求める
	static Vector3 axisLength[kObjectNum][kEdgeNum]{};//長さ
	for (int i = 0; i < kObjectNum; i++) {
		for (int j = 0; j < kEdgeNum; j++) {
			axisLength[i][j].x = std::abs(maxPos[i][j].x - minPos[i][j].x);
			axisLength[i][j].y = std::abs(maxPos[i][j].y - minPos[i][j].y);
			axisLength[i][j].z = std::abs(maxPos[i][j].z - minPos[i][j].z);
		}
	}

	//影の長さの合計
	static Vector3 sumAxisLength[kEdgeNum]{};//2つのオブジェクトを合わせた長さ
	for (int i = 0; i < kEdgeNum; i++) {
		sumAxisLength[i].x = axisLength[0][i].x + axisLength[1][i].x;
		sumAxisLength[i].y = axisLength[0][i].y + axisLength[1][i].y;
		sumAxisLength[i].z = axisLength[0][i].z + axisLength[1][i].z;
	}

	//2つの影の両端の差分
	static Vector3 differenceAxis[kEdgeNum]{};//二つの頂点の差分
	for (int i = 0; i < kEdgeNum; i++) {
		differenceAxis[i] = std::max(maxPos[0][i], maxPos[1][i]) - std::min(minPos[0][i], minPos[1][i]);
	}

	//影の長さ<2つの影の両端の差分を
	bool isHit = true;
	for (int i = 0; i < kEdgeNum; i++) {
		if (sumAxisLength[i].x <= differenceAxis[i].x ||
			sumAxisLength[i].y <= differenceAxis[i].y ||
			sumAxisLength[i].z <= differenceAxis[i].z) {
			isHit = false;
			break; // 一度衝突していないとわかれば、残りの計算をスキップ
		}

	}

	//ターゲットの当たり判定を実行
	target->OnCollision(isHit);
}




























