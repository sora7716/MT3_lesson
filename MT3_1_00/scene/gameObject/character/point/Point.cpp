#include "Point.h"
#include "scene/gameObject/camera/Camera.h"
#include <algorithm>
using namespace std;

//コンストラクタ
Point::Point() {
	t_ = {};
	project_ = {};
	closestPoint_ = {};
	point_ = {};
	segment_ = {};
	camera_ = nullptr;
	color_ = 0u;
	isHit_ = false;
}

//デストラクタ
Point::~Point() {

}

//初期化
void Point::Initialize(Camera* camera) {
	camera_ = camera;
	point_ = {};
	segment_ = { {-0.45f,0.41f,0.0f},{1.0f,0.58f,0.0f} };
	color_ = WHITE;
	isHit_ = false;
}

//更新処理
void Point::Update() {
	Project(point_ - segment_.origin, segment_.diff);
	ClosestPoint();
}


void Point::DebugText() {
	ImGui::DragFloat3("segment origin", &segment_.origin.x, 0.1f);
	ImGui::DragFloat3("segment diff", &segment_.diff.x, 0.1f);
	//ImGui::DragFloat3("point", &point_.x,0.1f);
	//ImGui::InputFloat3("Project", &project_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
	//ImGui::InputFloat3("cp", &closestPoint_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
}

//描画処理
void Point::Draw() {
	Vector3 start{};
	Vector3 end{};
	CameraScreenTransform(camera_, segment_.origin, start);
	CameraScreenTransform(camera_, (segment_.origin + segment_.diff), end);
	Novice::DrawLine(
		(int)start.x, (int)start.y,
		(int)end.x, (int)end.y,
		color_
	);
}

//衝突した場合の判定
void Point::OnCollision(){
	if (isHit_) {
		SetColor(RED);
	}
	else {
		SetColor(WHITE);
	}
}

//最近接点のゲッター
Vector3 Point::GetClosestPoint()const {
	return closestPoint_;
}

//原点のセッター
Vector3 Point::GetPoint()const {
	return point_;
}

//線分のゲッター
Point::Segment Point::GetSegment() const{
	return segment_;
}

//原点のセッター
void Point::SetPoint(const Vector3& point) {
	point_ = point;
}

//線分のセッター
void Point::SetSegment(const Segment& segment) {
	segment_ = segment;
}

//色のセッター
void Point::SetColor(uint32_t color) {
	color_ = color;
}

//衝突判定のセッター
void Point::SetIsHit(bool isHit){
	isHit_ = isHit;
}

//正射影ベクトル
void Point::Project(const Vector3& v1, const Vector3& v2) {
	float dot1 = Math::Dot(v1, v2);
	float length = Math::Dot(v2, v2);
	project_ = dot1 / length * v2;
	t_ = dot1 / length;
}


void Point::ClosestPoint() {
	t_ = clamp(t_, 0.0f, 1.0f);
	closestPoint_ = segment_.origin + segment_.diff * t_;
	//closestPoint_ = segment_.origin + project_;
}

