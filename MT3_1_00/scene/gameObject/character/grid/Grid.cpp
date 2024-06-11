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
		end_[xIndex].x = (-(float)kSubdivision / 2.0f + (float)xIndex) * kGridEvery;
		end_[xIndex].z = kGridHalfWidth;
		ndcVertexStart_[xIndex] = Math::Transform(localStart_[xIndex], camera_->GetViewProjectionMatrix());
		ndcVertexEnd_[xIndex] = Math::Transform(end_[xIndex], camera_->GetViewProjectionMatrix());
		screenStart_[xIndex] = Math::Transform(ndcVertexStart_[xIndex], camera_->GetViewportMatrix());
		screenEnd_[xIndex] = Math::Transform(ndcVertexEnd_[xIndex], camera_->GetViewportMatrix());
		Novice::DrawLine(
			(int)screenStart_[xIndex].x, (int)screenStart_[xIndex].y,
			(int)screenEnd_[xIndex].x, (int)screenEnd_[xIndex].y,
			color
		);
		if (xIndex == 4) {
			color = 0x00000088;
		}
		else {
			color = 0xFFFFFF88;
		}
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		localStart_[zIndex].z = (-(float)kSubdivision / 2.0f + (float)zIndex) * kGridEvery;
		localStart_[zIndex].x = -kGridHalfWidth;
		end_[zIndex].z = (-(float)kSubdivision / 2.0f + (float)zIndex) * kGridEvery;
		end_[zIndex].x = kGridHalfWidth;
		ndcVertexStart_[zIndex] = Math::Transform(localStart_[zIndex], camera_->GetViewProjectionMatrix());
		ndcVertexEnd_[zIndex] = Math::Transform(end_[zIndex], camera_->GetViewProjectionMatrix());
		screenStart_[zIndex] = Math::Transform(ndcVertexStart_[zIndex], camera_->GetViewportMatrix());
		screenEnd_[zIndex] = Math::Transform(ndcVertexEnd_[zIndex], camera_->GetViewportMatrix());
		Novice::DrawLine(
			(int)screenStart_[zIndex].x, (int)screenStart_[zIndex].y,
			(int)screenEnd_[zIndex].x, (int)screenEnd_[zIndex].y,
			color
		);

		if (zIndex == 4) {
			color = 0x00000088;
		}
		else {
			color = 0xFFFFFF88;
		}
	}
}
