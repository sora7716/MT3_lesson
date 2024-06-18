#include "Line.h"
#include <algorithm>
using namespace std;

//コンストラクタ
Line::Line(){
	t_ = {};
	project_ = {};
	closestPoint_ = {};
	point_ = {};
	segment_ = {};
}

//デストラクタ
Line::~Line(){

}

//初期化
void Line::Initialize(){
	point_ = {};
	segment_ = {};
}

//更新処理
void Line::Update(){
	Project(point_- segment_.origin,segment_.diff);
	ClosestPoint();
}


//描画処理
void Line::Draw(){

}

//最近接点のゲッター
Vector3 Line::GetClosestPoint(){
	return closestPoint_;
}

Vector3 Line::GetPoint(){
	return point_;
}

//原点のセッター
void Line::SetPoint(const Vector3& point){
	point_ = point;
}

//線分のセッター
void Line::SetSegment(const Segment& segment){
	segment_ = segment;
}

//正射影ベクトル
void Line::Project(const Vector3&v1, const Vector3& v2){
	float dot1 = Math::Dot(v1, v2);
	float dot2 = Math::Dot(v2, v2);
	project_ = dot1 / dot2 * v2;
	t_ = Math::Dot(v1, v2) / powf(Math::Length(v2),2.0f);
}


void Line::ClosestPoint(){
	//closestPoint_ = point_ + t_ * segment_.diff;
	closestPoint_ = point_ + project_;
}
