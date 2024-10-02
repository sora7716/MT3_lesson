#include "Character.h"

//ワールドビュープロジェクション
void Character::WvpMatrix(Camera* camera) {
	//ワールド座標系
	worldMatrix_ = Math::MakeAffineMatrix(scale_, rotate_, translate_);
	//wvpマトリックス
	worldViewProjectionMatrix_ = worldMatrix_ * camera->GetViewProjectionMatrix();
}

//ワールドビュープロジェクション
void Character::WvpMatrix(const Matrix4x4& viewProjection) {
	//ワールド座標系
	worldMatrix_ = Math::MakeAffineMatrix(scale_, rotate_, translate_);
	//wvpマトリックス
	worldViewProjectionMatrix_ = worldMatrix_ * viewProjection;
}

void Character::WvpMatrix(Camera* camera, Vector3& scale, Vector3& rotate, Vector3& translate) {
	//ワールド座標系
	worldMatrix_ = Math::MakeAffineMatrix(scale, rotate, translate);
	//wvpマトリックス
	worldViewProjectionMatrix_ = worldMatrix_ * camera->GetViewProjectionMatrix();
}

//ワールドビュープロジェクションだけの計算
void Character::WorldViewProjection(Camera* camera){
	//wvpマトリックス
	worldViewProjectionMatrix_ = worldMatrix_ * camera->GetViewProjectionMatrix();
}

//ワールドビュープロジェクション戻り値あり
Matrix4x4 Character::WorldViewProjectionMatrix(Camera* camera, Vector3 scale, Vector3 rotate, Vector3 translate) const {
	//ワールド座標系
	Matrix4x4 worldMatrix = Math::MakeAffineMatrix(scale, rotate, translate);
	//wvpマトリックス
	Matrix4x4 worldViewProjectionMatrix = worldMatrix_ * camera->GetViewProjectionMatrix();
	return worldViewProjectionMatrix;
}

//ローカルをスクリーンに座標変換
void Character::ScreenTransform(Camera* camera, const Vector3& kLocalVertices, Vector3& screenVertices) {
	//ワールドとワールドビュープロジェクションを求める
	WorldViewProjection(camera);
	//正規化デバイス座標系
	ndcVertex_ = Math::Transform(kLocalVertices, worldViewProjectionMatrix_);
	//スクリーン座標
	screenVertices = Math::Transform(ndcVertex_, camera->GetViewportMatrix());
}

//ローカルをスクリーンに座標変換
void Character::ScreenTransform(Camera* camera, const Vector3& kLocalVertices, Vector3& screenVertices, Vector3& scale, Vector3& rotate, Vector3& translate) {
	//ワールドとワールドビュープロジェクションを求める
	WvpMatrix(camera, scale, rotate, translate);
	//正規化デバイス座標系
	ndcVertex_ = Math::Transform(kLocalVertices, worldViewProjectionMatrix_);
	//スクリーン座標
	screenVertices = Math::Transform(ndcVertex_, camera->GetViewportMatrix());

}

//ローカルをスクリーンに変換
void Character::CameraScreenTransform(Camera* camera, const Vector3& kLocalVertices, Vector3& screenVertices) {
	//正規化デバイス座標系
	ndcVertex_ = Math::Transform(kLocalVertices, camera->GetViewProjectionMatrix());
	//スクリーン座標
	screenVertices = Math::Transform(ndcVertex_, camera->GetViewportMatrix());
}

// ワールドビュープロジェクションのゲッター
const Matrix4x4& Character::GetWorldViewProjection() {
	// TODO: return ステートメントをここに挿入します
	return worldViewProjectionMatrix_;
}

const Matrix4x4& Character::GetWorldMatrix() {
	// TODO: return ステートメントをここに挿入します
	return worldMatrix_;
}

//ワールド座標のゲッター
const Vector3 Character::GetWorldPosition() {
	return { worldMatrix_.m[3][0],worldMatrix_.m[3][1],worldMatrix_.m[3][2] };
}
