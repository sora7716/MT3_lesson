#include "Point.h"
#include "scene/gameObject/camera/Camera.h"
#include <algorithm>
using namespace std;

//コンストラクタ
Point::Point(){
	t_ = {};
	project_ = {};
	closestPoint_ = {};
	point_ = {};
	segment_ = {};
	camera_ = nullptr;
}

//デストラクタ
Point::~Point(){

}

//初期化
void Point::Initialize(Camera* camera){
	camera_ = camera;
	point_ = {};
	segment_ = {};
}

//更新処理
void Point::Update(){
	Project(point_- segment_.origin,segment_.diff);
	ClosestPoint();
}


void Point::DebugText(){
	ImGui::DragFloat3("point", &point_.x,0.1f);
	ImGui::DragFloat3("segment origin", &segment_.origin.x,0.1f);
	ImGui::DragFloat3("segment diff", &segment_.diff.x,0.1f);
	ImGui::InputFloat3("Project", &project_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
	ImGui::InputFloat3("cp", &closestPoint_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
}

//描画処理
void Point::Draw(){
	Vector3 start = Math::Transform(Math::Transform(segment_.origin, camera_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());
	Vector3 end = Math::Transform(Math::Transform(segment_.origin + segment_.diff, camera_->GetViewProjectionMatrix()), camera_->GetViewportMatrix());

	Novice::DrawLine(
		(int)start.x,(int)start.y,
		(int)end.x, (int)end.y,
		WHITE 
	);
}

//最近接点のゲッター
Vector3 Point::GetClosestPoint(){
	return closestPoint_;
}

Vector3 Point::GetPoint(){
	return point_;
}

//原点のセッター
void Point::SetPoint(const Vector3& point){
	point_ = point;
}

//線分のセッター
void Point::SetSegment(const Segment& segment){
	segment_ = segment;
}

//正射影ベクトル
void Point::Project(const Vector3&v1, const Vector3& v2){
	float dot1 = Math::Dot(v1, v2);
	float length = Math::Dot(v2, v2);
	project_ = dot1 / length * v2;
	t_ = dot1 / length;
}


void Point::ClosestPoint(){
	t_ = clamp(t_, 0.0f, 1.0f);
	closestPoint_ = segment_.origin + segment_.diff * t_;
	//closestPoint_ = segment_.origin + project_;
}

