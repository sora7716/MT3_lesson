#include <cassert>
#include <cmath>
#include "Math.h"
using namespace std;

//逆行列
MyMatrix4x4 Math::Inverse(MyMatrix4x4 m){
	Matrix4x4 result{};
	float determinant = m.GetMatrix4x4().m[0][0] * (m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[3][3] +
		m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[1][3] +
		m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[2][3] -
		m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[1][3] -
		m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[3][3] -
		m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[2][3]) -
		m.GetMatrix4x4().m[0][1] * (m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[1][3] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[2][3]) +
		m.GetMatrix4x4().m[0][2] * (m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][3] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][3]) -
		m.GetMatrix4x4().m[0][3] * (m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][2] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][2] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][2] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][2] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][2] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][2]);



	if (determinant != 0) {
		result.m[0][0] = (m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[1][3] +
			m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[2][3]) /
			determinant;

		result.m[0][1] = -(m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[2][3]) /
			determinant;

		result.m[0][2] = (m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[1][3]) /
			determinant;

		result.m[0][3] = -(m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[2][3] +
			m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[1][3]) /
			determinant;


		result.m[1][0] = -(m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[1][3] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[2][3]) /
			determinant;

		result.m[1][1] = (m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[2][3]) /
			determinant;

		result.m[1][2] = -(m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[3][2] * m.GetMatrix4x4().m[1][3]) /
			determinant;

		result.m[1][3] = (m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[2][3] +
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][2] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[0][2] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[2][2] * m.GetMatrix4x4().m[1][3]) /
			determinant;


		result.m[2][0] = (m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][3] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][3]) /
			determinant;

		result.m[2][1] = -(m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][3]) /
			determinant;

		result.m[2][2] = (m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][3] +
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[3][3] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][3]) /
			determinant;

		result.m[2][3] = -(m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][3] +
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[0][3] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[1][3] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[0][3] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[2][3] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][3]) /
			determinant;

		result.m[3][0] = -(m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][2] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][2] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][2] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][2] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][2] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][2]) /
			determinant;

		result.m[3][1] = (m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[3][2] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[0][2] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[2][2] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[0][2] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[3][2] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[2][2]) /
			determinant;

		result.m[3][2] = -(m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[3][2] +
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[0][2] +
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[1][2] -
			m.GetMatrix4x4().m[3][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[0][2] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[3][2] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[3][1] * m.GetMatrix4x4().m[1][2]) /
			determinant;

		result.m[3][3] = (m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[2][2] +
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[0][2] +
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[1][2] -
			m.GetMatrix4x4().m[2][0] * m.GetMatrix4x4().m[1][1] * m.GetMatrix4x4().m[0][2] -
			m.GetMatrix4x4().m[1][0] * m.GetMatrix4x4().m[0][1] * m.GetMatrix4x4().m[2][2] -
			m.GetMatrix4x4().m[0][0] * m.GetMatrix4x4().m[2][1] * m.GetMatrix4x4().m[1][2]) /
			determinant;
	}

	return result;
}

//転置行列
MyMatrix4x4 Math::Transpose(MyMatrix4x4 m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.GetMatrix4x4().m[j][i];
		}
	}

	return result;
}

//単位行列
Matrix4x4 Math::MakeIdentity4x4() {
	Matrix4x4 result{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};
	return result;
}

//拡縮
MyMatrix4x4 Math::MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{
		scale.x,0.0f,0.0f,0.0f,
		0.0f,scale.y,0.0f,0.0f,
		0.0f,0.0f,scale.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

//平行移動
MyMatrix4x4 Math::MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate.x,translate.y,translate.z,1.0f
	};
	return result;
}

//同次座標系で計算しデカルト座標系に変換
Vector3 Math::Transform(const Vector3& vector, MyMatrix4x4 matrix) {
	Vector3 result{};
	result.x = vector.x * matrix.GetMatrix4x4().m[0][0] + vector.y * matrix.GetMatrix4x4().m[1][0] + vector.z * matrix.GetMatrix4x4().m[2][0] + 1.0f * matrix.GetMatrix4x4().m[3][0];
	result.y = vector.x * matrix.GetMatrix4x4().m[0][1] + vector.y * matrix.GetMatrix4x4().m[1][1] + vector.z * matrix.GetMatrix4x4().m[2][1] + 1.0f * matrix.GetMatrix4x4().m[3][1];
	result.z = vector.x * matrix.GetMatrix4x4().m[0][2] + vector.y * matrix.GetMatrix4x4().m[1][2] + vector.z * matrix.GetMatrix4x4().m[2][2] + 1.0f * matrix.GetMatrix4x4().m[3][2];
	float w  = vector.x * matrix.GetMatrix4x4().m[0][3] + vector.y * matrix.GetMatrix4x4().m[1][3] + vector.z * matrix.GetMatrix4x4().m[2][3] + 1.0f * matrix.GetMatrix4x4().m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

//x座標を軸に回転
MyMatrix4x4 Math::MakeRotateXMatrix(float radian) {
	Matrix4x4 result{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cos(radian),sin(radian),0.0f,
		0.0f,-sin(radian),cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};
	return result;
}

//y座標を軸に回転
MyMatrix4x4 Math::MakeRotateYMatrix(float radian) {
	Matrix4x4 result{
		cos(radian),0.0f,-sin(radian),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sin(radian),0.0f,cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

//z座標を軸に回転
MyMatrix4x4 Math::MakeRotateZMatrix(float radian) {
	Matrix4x4 result{
		cos(radian),sin(radian),0.0f,0.0f,
		-sin(radian),cos(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

//x,y,z座標で回転
MyMatrix4x4 Math::MakeRotateXYZMatrix(Vector3 radian) {
	return MakeRotateXMatrix(radian.x)*MakeRotateYMatrix(radian.y)*MakeRotateZMatrix(radian.z);
}

//アフィン関数
MyMatrix4x4 Math::MakeAffineMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate) {
	return (MakeScaleMatrix(scale)*MakeRotateXYZMatrix(radian))*MakeTranslateMatrix(translate);
}

// 正射影行列
MyMatrix4x4 Math::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result{
		2.0f / (right - left),0.0f,0.0f,0.0f,
		0.0f,2.0f / (top - bottom),0.0f,0.0f,
		0.0f,0.0f,1.0f / (farClip - nearClip),0.0f,
		(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1.0f
	};

	return result;
}

//透視投影行列
MyMatrix4x4 Math::MakePerspectiveFovMatrix(float fovY, float aspectRation, float nearClip, float farClip) {
	Matrix4x4 result{
		1.0f / aspectRation * 1.0f / tan(fovY / 2.0f),0.0f,0.0f,0.0f,
		0.0f,1.0f / tan(fovY / 2.0f),0.0f,0.0f,
		0.0f,0.0f,farClip / (farClip - nearClip),1.0f,
		0.0f,0.0f,(nearClip * farClip / (farClip - nearClip)) * -1.0f,0.0f
	};

	return result;
}

//ビューポートマトリックス
MyMatrix4x4 Math::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{
		width / 2.0f,0.0f,0.0f,0.0f,
		0.0f,-height / 2.0f,0.0f,0.0f,
		0.0f,0.0f,maxDepth - minDepth,0.0f,
		left + width / 2.0f,top + height / 2.0f,minDepth,1.0f,
	};
	return result;
}

//クロス積
MyVector3 Math::Cross(MyVector3 v1, MyVector3 v2){
	Vector3 result{};
	result.x = v1.GetVector().y * v2.GetVector().z - v1.GetVector().z * v2.GetVector().y;
	result.y = v1.GetVector().z * v2.GetVector().x - v1.GetVector().x * v2.GetVector().z;
	result.z = v1.GetVector().x * v2.GetVector().y - v1.GetVector().y * v2.GetVector().x;
	return result;
}

//内積
float Math::Dot(MyVector3 v1, MyVector3 v2) {
	MyVector3 result = MyVector3();
	result = v1 * v2;
	float dot = result.GetVector().x + result.GetVector().y + result.GetVector().z;
	return dot;
}

//ノルム
float Math::Length(MyVector3 v) {
	MyVector3 result = MyVector3();
	result = v * v;
	float length = sqrtf(result.GetVector().x + result.GetVector().y + result.GetVector().z);
	return length;
}

//単位ベクトル
MyVector3 Math::Normalize(MyVector3 v) {
	float len = Length(v);
	v /= len;
	return v;
}


