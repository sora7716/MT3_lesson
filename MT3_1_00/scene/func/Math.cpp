#include <cassert>
#include <cmath>
#include "Math.h"
#define cont(theta) (1.0f/tanf(theta)) 
using namespace std;

//転置行列
Matrix4x4 Math::Transpose(Matrix4x4 m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
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
Matrix4x4 Math::MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{
		scale.x,0.0f,0.0f,0.0f,
		0.0f,scale.y,0.0f,0.0f,
		0.0f,0.0f,scale.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

//平行移動
Matrix4x4 Math::MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate.x,translate.y,translate.z,1.0f
	};
	return result;
}

//同次座標系で計算しデカルト座標系に変換
Vector3 Math::Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	//assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

//x座標を軸に回転
Matrix4x4 Math::MakeRotateXMatrix(const float& radian) {
	Matrix4x4 result{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cos(radian),sin(radian),0.0f,
		0.0f,-sin(radian),cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};
	return result;
}

//y座標を軸に回転
Matrix4x4 Math::MakeRotateYMatrix(const float& radian) {
	Matrix4x4 result{
		cos(radian),0.0f,-sin(radian),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sin(radian),0.0f,cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

//z座標を軸に回転
Matrix4x4 Math::MakeRotateZMatrix(const float& radian) {
	Matrix4x4 result{
		cos(radian),sin(radian),0.0f,0.0f,
		-sin(radian),cos(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return result;
}

//x,y,z座標で回転
Matrix4x4 Math::MakeRotateXYZMatrix(const Vector3& radian) {
	return MakeRotateXMatrix(radian.x) * MakeRotateYMatrix(radian.y) * MakeRotateZMatrix(radian.z);
}

// OBB用の回転行列
void Math::MakeOBBRotateMatrix(Vector3* orientations, const Vector3& rotate) {
	Matrix4x4 rotateMatrix = MakeRotateXYZMatrix(rotate);

	//回転行列からの抽出

	//X'
	orientations[0].x = rotateMatrix.m[0][0];
	orientations[0].y = rotateMatrix.m[0][1];
	orientations[0].z = rotateMatrix.m[0][2];

	//Y'
	orientations[1].x = rotateMatrix.m[1][0];
	orientations[1].y = rotateMatrix.m[1][1];
	orientations[1].z = rotateMatrix.m[1][2];

	//Z'
	orientations[2].x = rotateMatrix.m[2][0];
	orientations[2].y = rotateMatrix.m[2][1];
	orientations[2].z = rotateMatrix.m[2][2];
}

// OBB用のワールド行列
Matrix4x4 Math::MakeOBBWorldMatrix(const Vector3* orientations, const Vector3 center) {
	Matrix4x4 result{
		orientations[0].x,orientations[0].y,orientations[0].z,0.0f,
		orientations[1].x,orientations[1].y,orientations[1].z,0.0f,
		orientations[2].x,orientations[2].y,orientations[2].z,0.0f,
		center.x,center.y,center.z,1.0f,
	};
	return result;
}

//アフィン関数
Matrix4x4 Math::MakeAffineMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate) {
	return (MakeScaleMatrix(scale) * MakeRotateXYZMatrix(radian)) * MakeTranslateMatrix(translate);
}

//STRの変換
Matrix4x4 Math::MakeSTRMatrix(const Vector3& scale, const Vector3& radian, const Vector3& translate) {
	return MakeScaleMatrix(scale) * MakeTranslateMatrix(translate) * MakeRotateXYZMatrix(radian);
}

// 正射影行列
Matrix4x4 Math::MakeOrthographicMatrix(const float& left, const float& top, const float& right, const float& bottom, const float& nearClip, const float& farClip) {
	Matrix4x4 result{
		2.0f / (right - left),0.0f,0.0f,0.0f,
		0.0f,2.0f / (top - bottom),0.0f,0.0f,
		0.0f,0.0f,1.0f / (farClip - nearClip),0.0f,
		(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1.0f
	};

	return result;
}

//透視投影行列
Matrix4x4 Math::MakePerspectiveFovMatrix(const float& fovY, const float& aspectRation, const float& nearClip, const float& farClip) {
	Matrix4x4 result{
		1.0f / aspectRation * cont(fovY / 2.0f),0.0f,0.0f,0.0f,
		0.0f,cont(fovY / 2.0f),0.0f,0.0f,
		0.0f,0.0f,farClip / (farClip - nearClip),1.0f,
		0.0f,0.0f,-(nearClip * farClip) / (farClip - nearClip),0.0f
	};

	return result;
}

//ビューポートマトリックス
Matrix4x4 Math::MakeViewportMatrix(const float& left, const float& top, const float& width, const float& height, const float& minDepth, const float& maxDepth) {
	Matrix4x4 result{
		width / 2.0f,0.0f,0.0f,0.0f,
		0.0f,-height / 2.0f,0.0f,0.0f,
		0.0f,0.0f,maxDepth - minDepth,0.0f,
		(left + width) / 2.0f,(top + height) / 2.0f,minDepth,1.0f,
	};
	return result;
}

//クロス積
Vector3 Math::Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

//内積
float Math::Dot(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};
	result = v1 * v2;
	float dot = result.x + result.y + result.z;
	return dot;
}

//ノルム
float Math::Length(const Vector3& v) {
	Vector3 result = {};
	result = v * v;
	float length = sqrtf(result.x + result.y + result.z);
	return length;
}


//単位ベクトル
Vector3 Math::Normalize(const Vector3& v) {
	float len = Length(v);
	Vector3 result{};
	result = v / len;
	return v;
}

//正規化
float Math::Normalize(const float& num) {
	float len = powf(num, 2);
	if (len != 0.0f) {
		float result = num / len;
		return result;
	}
	return num;
}



