#include "AABB.h"
#include "scene/gameObject/camera/Camera.h"
#include <string>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

//コンストラクター
AABB::AABB() {
}

//デストラクター
AABB::~AABB() {
}

//初期化
void AABB::Initialize(Camera* camera, const AABBMaterial& aabb) {
	camera_ = camera;
	aabb_ = aabb;
}

//更新
void AABB::Update() {
	localVertecies_[0].leftTop = { aabb_.min.x,aabb_.max.y,aabb_.min.z };
	localVertecies_[0].rightTop = { aabb_.max.x,aabb_.max.y,aabb_.min.z };
	localVertecies_[0].leftBottom = { aabb_.min.x,aabb_.min.y,aabb_.min.z };
	localVertecies_[0].rightBottom = { aabb_.max.x,aabb_.min.y,aabb_.min.z };

	localVertecies_[1].leftTop = { aabb_.min.x,aabb_.max.y,aabb_.max.z };
	localVertecies_[1].rightTop = { aabb_.max.x,aabb_.max.y,aabb_.max.z };
	localVertecies_[1].leftBottom = { aabb_.min.x,aabb_.min.y,aabb_.max.z };
	localVertecies_[1].rightBottom = { aabb_.max.x,aabb_.min.y,aabb_.max.z };

	for (int i = 0; i < kAABB2DNum; i++) {
		ScreenTransform(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), localVertecies_[i].leftTop, screenVertecies_[i].leftTop);
		ScreenTransform(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), localVertecies_[i].rightTop, screenVertecies_[i].rightTop);
		ScreenTransform(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), localVertecies_[i].leftBottom, screenVertecies_[i].leftBottom);
		ScreenTransform(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), localVertecies_[i].rightBottom, screenVertecies_[i].rightBottom);
	}

}

#ifdef _DEBUG

//衝突したときの判定
void AABB::OnCollision(){
	if (aabb_.isHit) {
		SetColor(RED);
	}
	else {
		SetColor(WHITE);
	}
}
void AABB::DebugText(const char* type) {

	std::string minMoji = std::string(type) + ".min";
	ImGui::DragFloat3(minMoji.c_str(), &aabb_.min.x, 0.01f);

	std::string maxMoji = std::string(type) + ".max";
	ImGui::DragFloat3(maxMoji.c_str(), &aabb_.max.x, 0.01f);
}
#endif // _DEBUG

//描画
void AABB::Draw() {
	//正面と背面の生成
	for (int i = 0; i < kAABB2DNum; i++) {
		Novice::DrawLine((int)screenVertecies_[i].leftTop.x, (int)screenVertecies_[i].leftTop.y, (int)screenVertecies_[i].rightTop.x, (int)screenVertecies_[i].rightTop.y, aabb_.color);
		Novice::DrawLine((int)screenVertecies_[i].rightTop.x, (int)screenVertecies_[i].rightTop.y, (int)screenVertecies_[i].rightBottom.x, (int)screenVertecies_[i].rightBottom.y, aabb_.color);
		Novice::DrawLine((int)screenVertecies_[i].rightBottom.x, (int)screenVertecies_[i].rightBottom.y, (int)screenVertecies_[i].leftBottom.x, (int)screenVertecies_[i].leftBottom.y, aabb_.color);
		Novice::DrawLine((int)screenVertecies_[i].leftBottom.x, (int)screenVertecies_[i].leftBottom.y, (int)screenVertecies_[i].leftTop.x, (int)screenVertecies_[i].leftTop.y, aabb_.color);
	}
	//側面の生成
	Novice::DrawLine((int)screenVertecies_[0].leftTop.x, (int)screenVertecies_[0].leftTop.y, (int)screenVertecies_[1].leftTop.x, (int)screenVertecies_[1].leftTop.y, aabb_.color);
	Novice::DrawLine((int)screenVertecies_[0].rightTop.x, (int)screenVertecies_[0].rightTop.y, (int)screenVertecies_[1].rightTop.x, (int)screenVertecies_[1].rightTop.y, aabb_.color);
	Novice::DrawLine((int)screenVertecies_[0].leftBottom.x, (int)screenVertecies_[0].leftBottom.y, (int)screenVertecies_[1].leftBottom.x, (int)screenVertecies_[1].leftBottom.y, aabb_.color);
	Novice::DrawLine((int)screenVertecies_[0].rightBottom.x, (int)screenVertecies_[0].rightBottom.y, (int)screenVertecies_[1].rightBottom.x, (int)screenVertecies_[1].rightBottom.y, aabb_.color);
}

// 衝突したかどうかのセッター
void AABB::SetIsHit(bool isHit){
	aabb_.isHit = isHit;
}

//色のセッター
void AABB::SetColor(uint32_t color){
	aabb_.color = color;
}

//AABBの素材のゲッター
GameObject::AABBMaterial AABB::GetAABBMaterial() const{
	return aabb_;
}
