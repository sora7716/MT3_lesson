#include "Capsule.h"

//初期化
void Capsule::Initialize(Camera* camera, const CapsuleMaterial&& capsule) {
	//カメラを受け取る
	camera_ = camera;
	//カプセルの素材を受け取る
	capsule_ = capsule;
	for (int i = 0; i < 2; i++) {
		sphere_[i] = std::make_unique<Sphere>();
		sphere_[i]->Initialize(camera_);
	}
	sphere_[0]->SetSphere({ capsule_.origin,capsule_.radius,capsule_.color,capsule_.isHit });
	sphere_[1]->SetSphere({ (capsule_.origin - capsule_.diff),capsule_.radius,capsule_.color,capsule_.isHit });
	line_ = std::make_unique<Line>();
	/*line_->Initialize(camera_);
	line_->SetSegment({ capsule_.origin,capsule_.diff });
	line_->SetColor(capsule_.color);
	line_->SetIsHit(capsule_.isHit);*/
}

//更新
void Capsule::Updata() {
}

//描画
void Capsule::Draw() {
	for (int i = 0; i < 2; i++) {
		sphere_[i]->Draw();
    }
	//line_->DrawSegment();
}
