#include "Capsule.h"
#include <string>
#include <cmath>
#include "scene/func/Math.h"
using namespace std;

//初期化
void Capsule::Initialize(Camera* camera, const CapsuleMaterial&& capsule) {
	//カメラを受け取る
	camera_ = camera;
	//カプセルの素材を受け取る
	capsule_ = capsule;
	for (int i = 0; i < 2; i++) {
		sphere_[i] = make_unique<Sphere>();
		sphere_[i]->Initialize(camera_, { capsule_.segment.origin,capsule_.radius,capsule_.color,capsule_.isHit });
	}
	for (int i = 0; i < kLineNum; i++) {
		lines_[i] = make_unique<Line>();
		lines_[i]->Initialize(camera_, move(capsule_.segment));
	}
	centerLine_ = make_unique<Line>();
	centerLine_->Initialize(camera_, move(capsule_.segment));

}

//更新
void Capsule::Updata() {
	sphere_[0]->SetSphere({ capsule_.segment.origin,capsule_.radius,capsule_.color,capsule_.isHit });
	sphere_[1]->SetSphere({ (capsule_.segment.origin + capsule_.segment.diff),capsule_.radius,capsule_.color,capsule_.isHit });
	for (int i = 0; i < kLineNum; i++) {
		Vector3 newPos{
			capsule_.segment.origin.x,
			capsule_.segment.origin.y + sin(static_cast<float>(i * pi_f / 2.0f)) * capsule_.radius,
			capsule_.segment.origin.z + cos(static_cast<float>(i * pi_f / 2.0f)) * capsule_.radius,
		};
		lines_[i]->SetSegment({ newPos,capsule_.segment.diff });
		lines_[i]->SetColor(capsule_.color);
		lines_[i]->SetIsHit(capsule_.isHit);
	}
	centerLine_->SetSegment({ capsule_.segment.origin,capsule_.segment.diff });
	centerLine_->SetColor(GREEN);
	centerLine_->SetIsHit(capsule_.isHit);
}

//デバックテキスト
void Capsule::DebugText(const char* name) {
	string originMove = (string)name + ".origin";
	ImGui::DragFloat3(originMove.c_str(), &capsule_.segment.origin.x, 0.1f);
	string diffMove = (string)name + ".diff";
	ImGui::DragFloat3(diffMove.c_str(), &capsule_.segment.diff.x, 0.1f);
	string radiusMove = (string)name + ".radius";
	ImGui::SliderFloat(radiusMove.c_str(), &capsule_.radius, 0.1f, 2.0f);
}

//描画
void Capsule::Draw() {
	for (int i = 0; i < 2; i++) {
		sphere_[i]->Draw();
	}
	for (auto& line : lines_) {
		line->DrawSegment();
	}
	centerLine_->DrawSegment();
}

//カプセルの素材のセッター
void Capsule::SetCapsuleMaterial(const CapsuleMaterial& capsuleMaterial) {
	capsule_ = capsuleMaterial;
}

// カプセルの素材のゲッター
GameObject::CapsuleMaterial Capsule::GetCapsuleMaterial() {
	return capsule_;
}

//衝突したら
void Capsule::OnCollision(bool isHit) {
	if (isHit) {
		capsule_.color = RED;
	}
	else {
		capsule_.color = WHITE;
	}
}
