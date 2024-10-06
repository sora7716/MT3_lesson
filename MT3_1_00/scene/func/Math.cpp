#define NOMINMAX
#include <cassert>
#include <cmath>
#include "Math.h"
#define cont(theta) (1.0f/tanf(theta)) 
#include <algorithm>
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

//正射影ベクトル
Vector3 Math::Project(const Vector3& v1, const Vector3& v2) {
	float length = Math::Dot(v2, v2); // v2の長さの2乗

	// 0除算を避けるために長さがゼロでないか確認
	if (length == 0.0f) {
		return Vector3(0, 0, 0); // 長さが0のベクトルに射影すると結果は無効
	}

	float dot1 = Math::Dot(v1, v2);
	return (dot1 / length) * v2;
}

// トランスフォームノーマル
Vector3 Math::TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};
	return result;
}

// 線形補間
Vector3 Math::Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;
	result.x = v1.x + t * (v2.x - v1.x);
	result.y = v1.y + t * (v2.y - v1.y);
	result.z = v1.z + t * (v2.z - v1.z);

	return result;
}

// 線形補間
float Math::Lerp(const float& num1, const float& num2, float t) {
	float result;
	result = num1 + t * (num2 - num1);
	return result;
}

// 球面線形補間
Vector3 Math::SLerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 nv1 = Normalize(v1); // v1 の正規化ベクトル
	Vector3 nv2 = Normalize(v2); // v2 の正規化ベクトル
	float dot = Dot(nv1, nv2);   // 正規化されたベクトル同士の内積

	// 誤差により1.0fを超えるのを防ぐ
	dot = std::clamp(dot, -1.0f, 1.0f);

	// アークコサインでθの角度を求める
	float theta = std::acos(dot);
	float sinTheta = std::sin(theta);

	Vector3 normalizeVector;
	// ゼロ除算を防ぐ
	if (sinTheta < 1.0e-5) {
		normalizeVector = nv1;
	}
	else {
		// 球面線形補間したベクトル(単位ベクトル)
		float sinThetaFrom = std::sin((1 - t) * theta);
		float sinThetaTo = std::sin(t * theta);
		normalizeVector = (sinThetaFrom * nv1 + sinThetaTo * nv2) / sinTheta;
	}

	// ベクトルの長さはv1とv2の長さを線形補間
	float length1 = Length(v1);
	float length2 = Length(v2);
	// Lerpで補間ベクトルの長さを求める
	float length = Lerp(length1, length2, t);

	return normalizeVector * length;
}

// CatmullRom補間
Vector3 Math::CatmullRomInterpolation(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t) {
	const float s = 0.5f; // 1/2のこと

	float t2 = t * t;  // tの2乗
	float t3 = t2 * t; // tの3乗

	Vector3 e3 = p0 * -1 + 3 * p1 - 3 * p2 + p3;
	Vector3 e2 = 2 * p0 - 5 * p1 + 4 * p2 - p3;
	Vector3 e1 = p0 * -1 + p2;
	Vector3 e0 = 2 * p1;

	return s * (e3 * t3 + e2 * t2 + e1 * t + e0);
}

// CatmullRomスプライン曲線上の座標を得る
Vector3 Math::CatmullRomPosition(const std::vector<Vector3>& points, float t) {
	assert(points.size() >= 4 && "制御点は4点以上必要です");
	// 区間数は制御点の数-1
	size_t division = points.size() - 1;
	// 1区間の長さ(全体を1.0とした割合)
	float areaWidth = 1.0f / division;

	// 区間内の始点を0.0f、終点1.0fとしたときの現在位置
	float t_2 = std::fmod(t, areaWidth) * division;
	// 下限(0.0f)とz上限(1.0f)の範囲を収める
	t_2 = std::clamp(t_2, 0.0f, 1.0f);
	// 区間番号
	size_t index = static_cast<size_t>(t / areaWidth);
	// 区間番号が上限を超えないように収める
	index = std::min(index, division - 1);

	// 4点分のインデックス
	size_t index0 = index - 1;
	size_t index1 = index;
	size_t index2 = index + 1;
	size_t index3 = index + 2;

	// 最初の区間のp0はp1を重複使用する
	if (index == 0) {
		index0 = index1;
	}

	// 最後の区間のp3はp2を重複使用する
	if (index3 >= points.size()) {
		index3 = index2;
	}

	// 4点の座標
	const Vector3& p0 = points[index0];
	const Vector3& p1 = points[index1];
	const Vector3& p2 = points[index2];
	const Vector3& p3 = points[index3];

	// 4点を指定してCatmull-Rom補間
	return CatmullRomInterpolation(p0, p1, p2, p3, t_2);
}

// 三次元のベジエ曲線
Vector3 Math::Bezier(const Vector3* points, float t) {
	//制御点を分ける
	Vector3 p0 = points[0];//始点
	Vector3 p1 = points[1];//中点
	Vector3 p2 = points[2];//終点

	Vector3 p0p1 = Lerp(p0, p1, t);  // p0とp1の間を補間
	Vector3 p1p2 = Lerp(p1, p2, t);  // p1とp2の間を補間
	Vector3 p = Lerp(p0p1, p1p2, t); // 上記2つの補間結果をさらに補間
	return p;
}

// 三次元ベジエ曲線(球面線形補間ver)
Vector3 Math::BezierS(const Vector3* points, float t) {
	//制御点を分ける
	Vector3 p0 = points[0];//始点
	Vector3 p1 = points[1];//中点
	Vector3 p2 = points[2];//終点

	Vector3 p0p1 = SLerp(p0, p1, t);  // p0とp1の間を補間
	Vector3 p1p2 = SLerp(p1, p2, t);  // p1とp2の間を補間
	Vector3 p = SLerp(p0p1, p1p2, t); // 上記2つの補間結果をさらに補間
	return p;
}

