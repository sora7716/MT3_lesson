#include "Aithmetic.h"

//デフォルトコンストラクター
MyVector3::MyVector3() {
	vector = {};
}

//コンストラクター
MyVector3::MyVector3(Vector3 num) {
	vector = num;
}

//加算
MyVector3 MyVector3::operator+(const MyVector3& num) {
	MyVector3 result{};
	result.vector.x = vector.x + num.vector.x;
	result.vector.y = vector.y + num.vector.y;
	result.vector.z = vector.z + num.vector.z;
	return result;
}

//加算(複合)
MyVector3& MyVector3::operator+=(const MyVector3& num) {
	vector.x += num.vector.x;
	vector.y += num.vector.y;
	vector.z += num.vector.z;
	return *this;
}

//減算
MyVector3 MyVector3::operator-(const MyVector3& num) {
	MyVector3 result{};
	result.vector.x = vector.x - num.vector.x;
	result.vector.y = vector.y - num.vector.y;
	result.vector.z = vector.z - num.vector.z;
	return result;
}

//減算(複合)
MyVector3& MyVector3::operator-=(const MyVector3& num) {
	vector.x -= num.vector.x;
	vector.y -= num.vector.y;
	vector.z -= num.vector.z;
	return *this;
}

//スカラー倍
MyVector3 MyVector3::operator*(const float& k) {
	MyVector3 result{};
	result.vector.x = vector.x * k;
	result.vector.y = vector.y * k;
	result.vector.z = vector.z * k;
	return result;
}

//掛け算
MyVector3 MyVector3::operator*(const MyVector3& num) {
	MyVector3 result{};
	result.vector.x = vector.x * num.vector.x;
	result.vector.y = vector.y * num.vector.y;
	result.vector.z = vector.z * num.vector.z;
	return result;
}

//正規化
MyVector3& MyVector3::operator/=(const float& len) {
	if (len != 0.0f) {
		vector.x /= len;
		vector.y /= len;
		vector.z /= len;
	}
	return *this;
}

//ベクトルのゲッター
Vector3 MyVector3::GetVector() { return vector; }

//セッター
void MyVector3::SetVector(Vector3 num) {
	vector = num;
}

//デフォルトコンストラクター
MyMatrix4x4::MyMatrix4x4() {
	matrix4x4 = {};
}

//コンストラクター
MyMatrix4x4::MyMatrix4x4(Matrix4x4 num) {
	matrix4x4 = num;
}

//加算
MyMatrix4x4 MyMatrix4x4::operator+(const MyMatrix4x4& num) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix4x4.m[i][j] + num.matrix4x4.m[i][j];
		}
	}
	return result;
}

//加算(複合)
MyMatrix4x4& MyMatrix4x4::operator+=(const MyMatrix4x4& num) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix4x4.m[i][j] += num.matrix4x4.m[i][j];
		}
	}
	return *this;
}

//減算
MyMatrix4x4 MyMatrix4x4::operator-(const MyMatrix4x4& num) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix4x4.m[i][j] - num.matrix4x4.m[i][j];
		}
	}
	return result;
}

//減算(複合)
MyMatrix4x4& MyMatrix4x4::operator-=(const MyMatrix4x4& num) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix4x4.m[i][j] -= num.matrix4x4.m[i][j];
		}
	}
	return *this;
}

//掛け算
MyMatrix4x4 MyMatrix4x4::operator*(const MyMatrix4x4& num) {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += matrix4x4.m[i][k] * num.matrix4x4.m[k][j];
			}
		}
	}
	return result;
}

//逆行列
MyMatrix4x4 MyMatrix4x4::operator~() {
	Matrix4x4 result{};
	float determinant = matrix4x4.m[0][0] * (matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
		matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
		matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
		matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
		matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] -
		matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) -
		matrix4x4.m[0][1] * (matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
			matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
			matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
			matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
			matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] -
			matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) +
		matrix4x4.m[0][2] * (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] +
			matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3] +
			matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] -
			matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3] -
			matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] -
			matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) -
		matrix4x4.m[0][3] * (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] +
			matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2] +
			matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] -
			matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2] -
			matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] -
			matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]);



	if (determinant != 0) {
		result.m[0][0] = (matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
			matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
			matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
			matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
			matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] -
			matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
			determinant;

		result.m[0][1] = -(matrix4x4.m[0][1] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
			matrix4x4.m[2][1] * matrix4x4.m[3][2] * matrix4x4.m[0][3] +
			matrix4x4.m[3][1] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
			matrix4x4.m[3][1] * matrix4x4.m[2][2] * matrix4x4.m[0][3] -
			matrix4x4.m[2][1] * matrix4x4.m[0][2] * matrix4x4.m[3][3] -
			matrix4x4.m[0][1] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
			determinant;

		result.m[0][2] = (matrix4x4.m[0][1] * matrix4x4.m[1][2] * matrix4x4.m[3][3] +
			matrix4x4.m[1][1] * matrix4x4.m[3][2] * matrix4x4.m[0][3] +
			matrix4x4.m[3][1] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
			matrix4x4.m[3][1] * matrix4x4.m[1][2] * matrix4x4.m[0][3] -
			matrix4x4.m[1][1] * matrix4x4.m[0][2] * matrix4x4.m[3][3] -
			matrix4x4.m[0][1] * matrix4x4.m[3][2] * matrix4x4.m[1][3]) /
			determinant;

		result.m[0][3] = -(matrix4x4.m[0][1] * matrix4x4.m[1][2] * matrix4x4.m[2][3] +
			matrix4x4.m[1][1] * matrix4x4.m[2][2] * matrix4x4.m[0][3] +
			matrix4x4.m[2][1] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
			matrix4x4.m[2][1] * matrix4x4.m[1][2] * matrix4x4.m[0][3] -
			matrix4x4.m[1][1] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
			matrix4x4.m[0][1] * matrix4x4.m[2][2] * matrix4x4.m[1][3]) /
			determinant;


		result.m[1][0] = -(matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
			matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3] +
			matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] -
			matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3] -
			matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] -
			matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
			determinant;

		result.m[1][1] = (matrix4x4.m[0][0] * matrix4x4.m[2][2] * matrix4x4.m[3][3] +
			matrix4x4.m[2][0] * matrix4x4.m[3][2] * matrix4x4.m[0][3] +
			matrix4x4.m[3][0] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
			matrix4x4.m[3][0] * matrix4x4.m[2][2] * matrix4x4.m[0][3] -
			matrix4x4.m[2][0] * matrix4x4.m[0][2] * matrix4x4.m[3][3] -
			matrix4x4.m[0][0] * matrix4x4.m[3][2] * matrix4x4.m[2][3]) /
			determinant;

		result.m[1][2] = -(matrix4x4.m[0][0] * matrix4x4.m[1][2] * matrix4x4.m[3][3] +
			matrix4x4.m[1][0] * matrix4x4.m[3][2] * matrix4x4.m[0][3] +
			matrix4x4.m[3][0] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
			matrix4x4.m[3][0] * matrix4x4.m[1][2] * matrix4x4.m[0][3] -
			matrix4x4.m[1][0] * matrix4x4.m[0][2] * matrix4x4.m[3][3] -
			matrix4x4.m[0][0] * matrix4x4.m[3][2] * matrix4x4.m[1][3]) /
			determinant;

		result.m[1][3] = (matrix4x4.m[0][0] * matrix4x4.m[1][2] * matrix4x4.m[2][3] +
			matrix4x4.m[1][0] * matrix4x4.m[2][2] * matrix4x4.m[0][3] +
			matrix4x4.m[2][0] * matrix4x4.m[0][2] * matrix4x4.m[1][3] -
			matrix4x4.m[2][0] * matrix4x4.m[1][2] * matrix4x4.m[0][3] -
			matrix4x4.m[1][0] * matrix4x4.m[0][2] * matrix4x4.m[2][3] -
			matrix4x4.m[0][0] * matrix4x4.m[2][2] * matrix4x4.m[1][3]) /
			determinant;


		result.m[2][0] = (matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] +
			matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3] +
			matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] -
			matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3] -
			matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] -
			matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) /
			determinant;

		result.m[2][1] = -(matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[3][3] +
			matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[0][3] +
			matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[2][3] -
			matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[0][3] -
			matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[3][3] -
			matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[2][3]) /
			determinant;

		result.m[2][2] = (matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[3][3] +
			matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[0][3] +
			matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[1][3] -
			matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[0][3] -
			matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[3][3] -
			matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[1][3]) /
			determinant;

		result.m[2][3] = -(matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[2][3] +
			matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[0][3] +
			matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[1][3] -
			matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[0][3] -
			matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[2][3] -
			matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[1][3]) /
			determinant;

		result.m[3][0] = -(matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] +
			matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2] +
			matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] -
			matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2] -
			matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] -
			matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]) /
			determinant;

		result.m[3][1] = (matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[3][2] +
			matrix4x4.m[2][0] * matrix4x4.m[3][1] * matrix4x4.m[0][2] +
			matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[2][2] -
			matrix4x4.m[3][0] * matrix4x4.m[2][1] * matrix4x4.m[0][2] -
			matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[3][2] -
			matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[2][2]) /
			determinant;

		result.m[3][2] = -(matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[3][2] +
			matrix4x4.m[1][0] * matrix4x4.m[3][1] * matrix4x4.m[0][2] +
			matrix4x4.m[3][0] * matrix4x4.m[0][1] * matrix4x4.m[1][2] -
			matrix4x4.m[3][0] * matrix4x4.m[1][1] * matrix4x4.m[0][2] -
			matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[3][2] -
			matrix4x4.m[0][0] * matrix4x4.m[3][1] * matrix4x4.m[1][2]) /
			determinant;

		result.m[3][3] = (matrix4x4.m[0][0] * matrix4x4.m[1][1] * matrix4x4.m[2][2] +
			matrix4x4.m[1][0] * matrix4x4.m[2][1] * matrix4x4.m[0][2] +
			matrix4x4.m[2][0] * matrix4x4.m[0][1] * matrix4x4.m[1][2] -
			matrix4x4.m[2][0] * matrix4x4.m[1][1] * matrix4x4.m[0][2] -
			matrix4x4.m[1][0] * matrix4x4.m[0][1] * matrix4x4.m[2][2] -
			matrix4x4.m[0][0] * matrix4x4.m[2][1] * matrix4x4.m[1][2]) /
			determinant;
	}

	return result;
}

//マトリックスのゲッター
Matrix4x4 MyMatrix4x4::GetMatrix4x4() { return matrix4x4; }

//マトリックスのセッター
void MyMatrix4x4::SetMatrix4x4(Matrix4x4 num) {
	matrix4x4 = num;
}

const Vector3 operator+=(const Vector3& num1,const Vector3& num2){
	Vector3 result{};
	result.x = num1.x + num2.x;
	result.y = num1.y + num2.y;
	result.z = num1.z + num2.z;
	return result;
}
