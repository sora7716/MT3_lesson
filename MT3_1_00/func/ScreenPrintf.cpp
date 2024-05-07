#include <Novice.h>
#include "ScreenPrintf.h"

//マトリックスのスクリーンプリント
void ScreenPrintf::MatrixScreenPrintf(int x, int y, Matrix4x4 matrix, const char* label){
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, (y + row * kRowHeight) + 20, "%6.02f", matrix.m[row][column]);
		}
	}
}

//ベクトルのスクリーンプリント
void ScreenPrintf::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label){
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}
