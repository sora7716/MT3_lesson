#include "Plane.h"
#include "scene/gameObject/camera/Camera.h"
#include "scene/gameObject/character/grid/Grid.h"
//コンストラクタ
Plane::Plane() {
	camera_ = nullptr;
	plane_ = {};
	plane_.color = WHITE;
}

//デストラクタ
Plane::~Plane() {
}

//初期化
void Plane::Initialize(Camera* camera) {
	camera_ = camera;
	plane_ = {{ 0.0f,1.0f,0.0f },1.0f,WHITE };
}

//更新処理
void Plane::Update() {
}

#ifdef _DEBUG
//デバックテキスト
void Plane::DebugText(){
	ImGui::DragFloat3("Plane.Normalize", &plane_.normal.x, 0.01f);
	plane_.normal = Math::Normalize(plane_.normal);
	ImGui::DragFloat("Plane.distance", &plane_.distance, 0.01f);
}
#endif // _DEBUG

//描画処理
void Plane::Draw() {
	Vector3 center = plane_.distance * plane_.normal;
	Vector3 perpendiculars[4]{};
	
	perpendiculars[0] = Math::Normalize(Perpendicular(plane_.normal));//1
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };//2
	perpendiculars[2] = Math::Cross(plane_.normal, perpendiculars[0]);//3
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };//4
	Vector3 points[4]{};
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = 2.0f * perpendiculars[index];
		Vector3 point = center + extend;
		points[index] = Math::Transform(Math::Transform(point, camera_ ->GetViewProjectionMatrix()), camera_->GetViewportMatrix());
	}

	Novice::DrawLine(
		(int)points[0].x, (int)points[0].y,
		(int)points[2].x, (int)points[2].y,
		plane_.color
	);
	Novice::DrawLine(
		(int)points[1].x, (int)points[1].y,
		(int)points[2].x, (int)points[2].y,
		plane_.color
	);
	Novice::DrawLine(
		(int)points[0].x, (int)points[0].y,
		(int)points[3].x, (int)points[3].y,
		plane_.color
	);
	Novice::DrawLine(
		(int)points[1].x, (int)points[1].y,
		(int)points[3].x, (int)points[3].y,
		plane_.color
	);

}

//平面の素材のゲッター
const Plane::PlaneMaterial& Plane::GetPlaneMaterial(){
	// TODO: return ステートメントをここに挿入します
	return plane_;
}

//平面の素材のセッター
void Plane::SetPlane(const PlaneMaterial& material){
plane_ = material;
}

//垂直
Vector3 Plane::Perpendicular(const Vector3& v) {
	if (v.x != 0.0f || v.y != 0.0f) {
		return { -v.y,v.x,0.0f };
	}
	else {
		return { 0.0f,-v.z,v.y };
	}
}
