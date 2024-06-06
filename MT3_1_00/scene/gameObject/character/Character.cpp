#include "Character.h"

//ローカルをスクリーンに座標変換
void Character::ScreenTransform(Camera*camera,MyMatrix4x4& worldMatrix,MyMatrix4x4& worldViewProjectionMatrix,const MyVector3*kLocalVertices,MyVector3&ndcVertex,MyVector3* screenVertices,uint32_t verticesNum) {
	//ワールド座標系
	worldMatrix = Math::MakeAffineMatrix(scale_.GetVector(), rotate_.GetVector(), translate_.GetVector());
	//wvpマトリックス
	worldViewProjectionMatrix = worldMatrix * camera->GetViewProjectionMatrix();
	for (uint32_t i = 0; i < verticesNum; ++i) {
		//正規化デバイス座標系
		ndcVertex = Math::Transform(kLocalVertices[i], worldViewProjectionMatrix);
		//スクリーン座標
		screenVertices[i] = Math::Transform(ndcVertex, camera->GetViewportMatrix());
	}
}
