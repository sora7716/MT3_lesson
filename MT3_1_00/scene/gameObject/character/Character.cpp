#include "Character.h"

//ローカルをスクリーンに座標変換
void Character::ScreenTransform(Camera*camera) {
	//ワールド座標系
	worldMatrix_ = Math::MakeAffineMatrix(scale_.GetVector(), rotate_.GetVector(), translate_.GetVector());
	//wvpマトリックス
	worldViewProjectionMatrix = worldMatrix_ * camera->GetViewProjectionMatrix();
	for (uint32_t i = 0; i < 3; ++i) {
		//正規化デバイス座標系
		ndcVertex = Math::Transform(kLocalVertices_[i], worldViewProjectionMatrix);
		//スクリーン座標
		screenVertices_[i] = Math::Transform(ndcVertex, camera->GetViewportMatrix());
	}
}
