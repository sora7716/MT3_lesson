#include "Grid.h"
#include "scene/gameObject/camera/Camera.h"

void Grid::Initialize(Camera* camera){
	camera_ = camera;//カメラのコピー
}

void Grid::Update(){
}

void Grid::Draw(){
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / (float)kSubdivision;
	
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		start_[xIndex].x = (-5.0f + xIndex) * kGridEvery;
		start_[xIndex].z = -kGridHalfWidth;
		end_[xIndex].x   = (-5.0f + xIndex) * kGridEvery;
		end_[xIndex].z   = kGridHalfWidth;
		ndcVertexStart_[xIndex] = Math::Transform(start_[xIndex], camera_->GetViewProjectionMatrix());
		ndcVertexEnd_[xIndex]   = Math::Transform(end_[xIndex],   camera_->GetViewProjectionMatrix());
		screenStart_[xIndex]    = Math::Transform(ndcVertexStart_[xIndex], camera_->GetViewportMatrix());
		screenEnd_[xIndex]      = Math::Transform(ndcVertexEnd_[xIndex], camera_->GetViewportMatrix());
		Novice::DrawLine(
			(int)screenStart_[xIndex].GetVector().x, (int)screenStart_[xIndex].GetVector().y,
			(int)screenEnd_[xIndex].GetVector().x, (int)screenEnd_[xIndex].GetVector().y,
			WHITE
		);
		Novice::ScreenPrintf(0, 30 * xIndex,   "%f", start_[xIndex].x);
		Novice::ScreenPrintf(100, 30 * xIndex, "%f", end_[xIndex].x);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		start_[zIndex].z = (-5.0f + zIndex) * kGridEvery;
		start_[zIndex].x = -kGridHalfWidth;
		end_[zIndex].z   = (-5.0f + zIndex) * kGridEvery;
		end_[zIndex].x   = kGridHalfWidth;
		ndcVertexStart_[zIndex] = Math::Transform(start_[zIndex], camera_->GetViewProjectionMatrix());
		ndcVertexEnd_[zIndex]   = Math::Transform(end_[zIndex],   camera_->GetViewProjectionMatrix());
		screenStart_[zIndex]    = Math::Transform(ndcVertexStart_[zIndex], camera_->GetViewportMatrix());
		screenEnd_[zIndex]      = Math::Transform(ndcVertexEnd_[zIndex], camera_->GetViewportMatrix());
		Novice::DrawLine(
			(int)screenStart_[zIndex].GetVector().x, (int)screenStart_[zIndex].GetVector().y,
			(int)screenEnd_[zIndex].GetVector().x, (int)screenEnd_[zIndex].GetVector().y,
			WHITE
		);
		Novice::ScreenPrintf(300, 30 * zIndex, "%f", start_[zIndex].z);
		Novice::ScreenPrintf(500, 30 * zIndex, "%f", end_[zIndex].z);
	}
}
