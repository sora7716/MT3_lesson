#include "Grid.h"
#include "scene/gameObject/camera/Camera.h"

void Grid::Initialize(Camera* camera) {
	camera_ = camera;//カメラのコピー
}

void Grid::Update() {
}

void Grid::Draw() {
	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / (float)kSubdivision;//1つ分の長さ

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		localStart_[xIndex].x = (-(float)kSubdivision/2.0f + (float)xIndex) * kGridEvery;
		localStart_[xIndex].z = -kGridHalfWidth;
		
		locakEnd_[xIndex].x = (-(float)kSubdivision / 2.0f + (float)xIndex) * kGridEvery;
		locakEnd_[xIndex].z = kGridHalfWidth;
		
		Character::CameraScreenTransform(camera_, localStart_[xIndex],screenStart_[xIndex]);
		Character::CameraScreenTransform(camera_, locakEnd_[xIndex],screenEnd_[xIndex]);

		Novice::DrawLine(
			(int)screenStart_[xIndex].x, (int)screenStart_[xIndex].y,
			(int)screenEnd_[xIndex].x, (int)screenEnd_[xIndex].y,
			color
		);
		if (xIndex == kSubdivision / 2 - 1) {
			color = 0x00000088;
		}
		else {
			color = 0xFFFFFF88;
		}
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		localStart_[zIndex].z = (-(float)kSubdivision / 2.0f + (float)zIndex) * kGridEvery;
		localStart_[zIndex].x = -kGridHalfWidth;
		locakEnd_[zIndex].z = (-(float)kSubdivision / 2.0f + (float)zIndex) * kGridEvery;
		locakEnd_[zIndex].x = kGridHalfWidth;

		Character::CameraScreenTransform(camera_, localStart_[zIndex], screenStart_[zIndex]);
		Character::CameraScreenTransform(camera_, locakEnd_[zIndex], screenEnd_[zIndex]);
		
		Novice::DrawLine(
			(int)screenStart_[zIndex].x, (int)screenStart_[zIndex].y,
			(int)screenEnd_[zIndex].x, (int)screenEnd_[zIndex].y,
			color
		);

		if (zIndex == kSubdivision / 2 - 1) {
			color = 0x00000088;  
		}
		else {
			color = 0xFFFFFF88;
		}
	}
}
