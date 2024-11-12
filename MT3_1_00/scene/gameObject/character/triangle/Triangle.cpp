#include "Triangle.h"
#include <string>
using namespace std;

//初期化
void Triangle::Initialize(Camera* camera, TriangleMaterial&& triangleMaterial){
	camera_ = camera;
	triangle_ = triangleMaterial;
}

//更新
void Triangle::Update(){
	for (int i = 0; i < kVertexNum; i++) {
		float theta = 120.0f * static_cast<float>(i);
		float angle = theta * rad;
		//正面
		localVertex_[0][i].x = triangle_.size.x * std::cosf(angle) + triangle_.center.x;
		localVertex_[0][i].y = triangle_.center.y + triangle_.size.y;
		localVertex_[0][i].z = triangle_.size.z * std::sinf(angle) + triangle_.center.z;
		//背面
		localVertex_[1][i].x = triangle_.size.x * std::cosf(angle) + triangle_.center.x;
		localVertex_[1][i].y = triangle_.center.y - triangle_.size.y;
		localVertex_[1][i].z = triangle_.size.z * std::sinf(angle) + triangle_.center.z;
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			CameraScreenTransform(camera_, localVertex_[i][j], screenVertex_[i][j]);
		}
	}
}

//デバックテキスト
void Triangle::DebugText(const char* label){
	(void)label;
}

//描画
void Triangle::Draw(){
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < kVertexNum; j++) {
			Novice::DrawLine((int)screenVertex_[i][j - 1].x, (int)screenVertex_[i][j - 1].y, (int)screenVertex_[i][j].x, (int)screenVertex_[i][j].y, triangle_.color);
			Novice::DrawLine((int)screenVertex_[0][j].x, (int)screenVertex_[0][j].y, (int)screenVertex_[1][j].x, (int)screenVertex_[1][j].y, triangle_.color);
		}
		//Novice::DrawLine((int)screenVertex_[i][2].x, (int)screenVertex_[i][2].y, (int)screenVertex_[i][0].x, (int)screenVertex_[i][0].y, triangle_.color);
	}
	Novice::DrawLine((int)screenVertex_[0][0].x, (int)screenVertex_[0][0].y, (int)screenVertex_[1][0].x, (int)screenVertex_[1][0].y, triangle_.color);
}

// ローカルの頂点
Vector3* Triangle::GetLocalVertex(int i){
	return localVertex_[i];
}

//三角柱のゲッター
GameObject::TriangleMaterial Triangle::GetTriangleMaterial(){
	return triangle_;
}

//法線ベクトルの作成
void Triangle::CreateNormal(){
	//面の法線を算出
	Vector3 v01 = GetLocalVertex(0)[1] - GetLocalVertex(0)[0];
	Vector3 v1101 = GetLocalVertex(0)[1] - GetLocalVertex(1)[1];

	Vector3 v12 = GetLocalVertex(0)[2] - GetLocalVertex(0)[1];
	Vector3 v1202 = GetLocalVertex(0)[2] - GetLocalVertex(1)[2];

	Vector3 v20 = GetLocalVertex(0)[0] - GetLocalVertex(0)[2];
	Vector3 v1000 = GetLocalVertex(0)[0] - GetLocalVertex(1)[0];

	//面の法線
	triangle_.normal[0] = Math::Normalize(Math::Cross(v01, v1101));
	triangle_.normal[1] = Math::Normalize(Math::Cross(v12, v1202));
	triangle_.normal[2] = Math::Normalize(Math::Cross(v20, v1000));
}