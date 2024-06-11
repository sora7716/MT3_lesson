#include "Character.h"

void Character::WvpMatrix(Camera* camera){
	//ワールド座標系
	worldMatrix_ = Math::MakeAffineMatrix(scale_,rotate_, translate_);
	//wvpマトリックス
	worldViewProjectionMatrix_ = worldMatrix_ * camera->GetViewProjectionMatrix();
}

//ローカルをスクリーンに座標変換
void Character::ScreenTransform(Camera*camera,const Vector3*kLocalVertices,Vector3* screenVertices,uint32_t elementCount) {
	WvpMatrix(camera);
	for (uint32_t i = 0; i < elementCount; ++i) {
		//正規化デバイス座標系
		ndcVertex_ = Math::Transform(kLocalVertices[i], worldViewProjectionMatrix_);
		//スクリーン座標
		screenVertices[i] = Math::Transform(ndcVertex_, camera->GetViewportMatrix());
	}
}

