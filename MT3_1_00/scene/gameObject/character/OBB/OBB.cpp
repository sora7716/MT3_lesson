#include "OBB.h"
#include "scene/func/Math.h"
#include "scene/gameObject/camera/Camera.h"
#include "scene/gameObject/character/AABB/AABB.h"
#include <string>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
using namespace std;


//初期化
void OBB::Initialize(Camera* camera, const OBBMaterial&& obbMaterial) {
	camera_ = camera;//カメラを受け取る
	//OBBの値を設定
	obb_ = obbMaterial;
	//角度
	rotate_ = obbMaterial.rotation;
	//色を決める
	aabb_.color = obb_.color;
}

//更新
void OBB::Update() {
	//サイズを設定
	aabb_.min = -obb_.size;
	aabb_.max = obb_.size;

	MakeVertecies();//頂点を作成
	Math::MakeOBBRotateMatrix(obb_.orientations, rotate_);//OBB用の回転行列を抽出
	worldMatrix_ = Math::MakeOBBWorldMatrix(obb_.orientations, obb_.center);//OBB用のワールド行列を作成
	//正規化しておく
	for (int i = 0; i < 3; i++) {
		obb_.orientations[i] = Math::Normalize(obb_.orientations[i]);
	}
	//スクリーン座標に変換
	for (int i = 0; i < kAABB2DNum; i++) {
		ScreenTransform(camera_, localVertecies_[i].leftTop, screenVertecies_[i].leftTop);
		ScreenTransform(camera_, localVertecies_[i].rightTop, screenVertecies_[i].rightTop);
		ScreenTransform(camera_, localVertecies_[i].leftBottom, screenVertecies_[i].leftBottom);
		ScreenTransform(camera_, localVertecies_[i].rightBottom, screenVertecies_[i].rightBottom);
	}
}

//デバックテキスト
void OBB::DebagText(const char* type) {
	string sizeMoji = string(type) + "size";
	ImGui::SliderFloat3(sizeMoji.c_str(), &obb_.size.x, 0.0f, 3.0f);
	string rotateMoji = string(type) + ".rotation";
	ImGui::DragFloat3(rotateMoji.c_str(), &rotate_.x, 0.01f);
	string translationMoji = string(type) + ".translation";
	ImGui::DragFloat3(translationMoji.c_str(), &obb_.center.x, 0.01f);
}

//描画
void OBB::Draw() {
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

// ワールドマトリックス逆行列のゲッター
Matrix4x4 OBB::GetOBBWorldMatrixInvers()const {
	Matrix4x4 obbWorldMatrixInvers = ~worldMatrix_;
	return obbWorldMatrixInvers;
}

//サイズのゲッター
Vector3 OBB::GetSize()const {
	return obb_.size;
}

// OBBのマテリアルのゲッター
GameObject::OBBMaterial OBB::GetOBBMaterial()const {
	return obb_;
}

// ローカルの頂点
GameObject::Vertex2D* OBB::GetLocalVertex() {
	return localVertecies_;
}

void OBB::OnCollision(bool isHit) {
	if (isHit) {
		aabb_.color = RED;
	}
	else {
		aabb_.color = obb_.color;
	}
}

//頂点を作成
void OBB::MakeVertecies() {
	localVertecies_[0].leftTop = { aabb_.min.x,aabb_.max.y,aabb_.min.z };
	localVertecies_[0].rightTop = { aabb_.max.x,aabb_.max.y,aabb_.min.z };
	localVertecies_[0].leftBottom = { aabb_.min.x,aabb_.min.y,aabb_.min.z };
	localVertecies_[0].rightBottom = { aabb_.max.x,aabb_.min.y,aabb_.min.z };

	localVertecies_[1].leftTop = { aabb_.min.x,aabb_.max.y,aabb_.max.z };
	localVertecies_[1].rightTop = { aabb_.max.x,aabb_.max.y,aabb_.max.z };
	localVertecies_[1].leftBottom = { aabb_.min.x,aabb_.min.y,aabb_.max.z };
	localVertecies_[1].rightBottom = { aabb_.max.x,aabb_.min.y,aabb_.max.z };
}
