#include "Line.h"
#include "scene/gameObject/camera/Camera.h"
#include <algorithm>
#include <string>
using namespace std;

//コンストラクタ
Line::Line() {
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
Line::~Line() {

}

//初期化
void Line::Initialize(Camera* camera, const Segment&& segment) {
	camera_ = camera;
	point_ = {};
	segment_ = segment;
	color_ = WHITE;
	isHit_ = false;
}

//更新処理
void Line::Update() {
	Project(point_ - segment_.origin, segment_.diff);
	ClosestPoint();
}


#ifdef _DEBUG
/// <summary>
/// デバックテキスト
/// </summary>
void Line::DebugText(const char*name) {
	string originLabel = string(name) + ".origin";
	ImGui::DragFloat3(originLabel.c_str(), &segment_.origin.x, 0.1f);
	string diffLabel = string(name) + ".diff";
	ImGui::DragFloat3(diffLabel.c_str(), &segment_.diff.x, 0.1f);
	//ImGui::DragFloat3("bezierPints[0]", &bezierPoints_[0].x, 0.1f);
	//ImGui::DragFloat3("bezierPints[1]", &bezierPoints_[1].x, 0.1f);
	//ImGui::DragFloat3("bezierPints[2]", &bezierPoints_[2].x, 0.1f);
	//ImGui::DragFloat3("point", &point_.x,0.1f);
	//ImGui::InputFloat3("Project", &project_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
	//ImGui::InputFloat3("cp", &closestPoint_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
	//ImGui::DragFloat3("catmullRomPoint[0]", &catmullRomPoints_[0].x, 0.1f);
	//ImGui::DragFloat3("catmullRomPoint[1]", &catmullRomPoints_[1].x, 0.1f);
	//ImGui::DragFloat3("catmullRomPoint[2]", &catmullRomPoints_[2].x, 0.1f);
	//ImGui::DragFloat3("catmullRomPoint[3]", &catmullRomPoints_[3].x, 0.1f);
}
#endif // _DEBUG

//線分の描画
void Line::DrawSegment() {
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

//ベジエ曲線の描画
void Line::DrawBezier() {
	for (int i = 0; i < kDivision; i++) {
		//フレームを分割
		float frame[2] = { static_cast<float>(i) / kDivision,static_cast<float>(i + 1) / kDivision};
		//ベジエ曲線
		Vector3 bezier[2];
		for (int j = 0; j < 2; j++) {
			bezier[j] = Math::Bezier(bezierPoints_, frame[j]);
		}
		//ベジエ曲線の始点と終点
		Vector3 start{};
		Vector3 end{};
		//スクリーン座標に変換
		CameraScreenTransform(camera_, bezier[0], bezier[0]);
		CameraScreenTransform(camera_, bezier[1], bezier[1]);
		//描画
		Novice::DrawLine(
			(int)bezier[0].x, (int)bezier[0].y,
			(int)bezier[1].x, (int)bezier[1].y,
			color_
		);
	}
}

// スプライン曲線
void Line::DrawCatmullRom(){
	for (int i = 0; i < kDivision; i++) {
		//フレームを分割
		float frame[2] = { static_cast<float>(i) / kDivision,static_cast<float>(i + 1) / kDivision };
		//ベジエ曲線
		Vector3 catmullRom[2];
		for (int j = 0; j < 2; j++) {
			catmullRom[j] = Math::CatmullRomPosition(catmullRomPoints_, frame[j]);
		}

		//スクリーン座標に変換
		CameraScreenTransform(camera_, catmullRom[0], catmullRom[0]);
		CameraScreenTransform(camera_, catmullRom[1], catmullRom[1]);
		//描画
		Novice::DrawLine(
			(int)catmullRom[0].x, (int)catmullRom[0].y,
			(int)catmullRom[1].x, (int)catmullRom[1].y,
			color_
		);
	}
}

//衝突した場合の判定
void Line::OnCollision(bool isHit) {
	isHit_ = isHit;
	if (isHit_) {
		SetColor(RED);
	}
	else {
		SetColor(WHITE);
	}
}

//最近接点のゲッター
Vector3 Line::GetClosestPoint()const {
	return closestPoint_;
}

//原点のセッター
Vector3 Line::GetPoint()const {
	return point_;
}

//線分のゲッター
Line::Segment Line::GetSegment() const {
	return segment_;
}

//正射影ベクトルのゲッター
Vector3 Line::GetProject() const {
	return project_;
}

//媒介変数のゲッター
float Line::GetT() const {
	return t_;
}

//原点のセッター
void Line::SetPoint(const Vector3& point) {
	point_ = point;
}

//線分のセッター
void Line::SetSegment(const Segment& segment) {
	segment_ = segment;
}

//色のセッター
void Line::SetColor(uint32_t color) {
	color_ = color;
}

//衝突判定のセッター
void Line::SetIsHit(bool isHit) {
	isHit_ = isHit;
}

// ベジエ曲線の制御点のセッター
void Line::SetBezierPoints(Vector3* controlPoints) {
	for (int i = 0; i < 3; i++) {
		bezierPoints_[i] = controlPoints[i];
	}
}

// ベジエ曲線の制御点のゲッター
Vector3* Line::GetBezierPoints(){
	return bezierPoints_;
}

// スプライン曲線の制御点のセッター
void Line::SetCatmullRomPoints(std::vector<Vector3> controlPoints){
	catmullRomPoints_ = controlPoints;
}

// スプライン曲線の制御点のゲッター
std::vector<Vector3> Line::GetCatmullRomPoints(){
	return catmullRomPoints_;
}

//正射影ベクトル
void Line::Project(const Vector3& v1, const Vector3& v2) {
	float dot1 = Math::Dot(v1, v2);
	float length = Math::Dot(v2, v2);
	project_ = dot1 / length * v2;
	t_ = dot1 / length;
}

// 最近接点
void Line::ClosestPoint() {
	t_ = clamp(t_, 0.0f, 1.0f);
	closestPoint_ = segment_.origin + segment_.diff * t_;
	//closestPoint_ = segment_.origin + project_;
}

