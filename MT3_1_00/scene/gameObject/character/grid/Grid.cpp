﻿#include "Grid.h"
#include "scene/gameObject/camera/Camera.h"
#include "scene/func/Aithmetic.h"


Grid::Grid() {
	camera_ = nullptr;//カメラ
	for (int i = 0; i < kElementCount; i++) {

		gridScale_[i] = {};
		gridRotate_[i] = {};
		gridTranslate_[i] = { 0.0f,0.0f,0.0f };
		//線の始点↓
		localStart_[i] = {};  //位置
		ndcVertexStart_[i] = {};//正規化デバイス座標
		screenStart_[i] = {};//スクリーン座標
		//線の始点↑

		//線の終点↓
		locakEnd_[i] = {};    //位置
		ndcVertexEnd_[i] = {};//正規化デバイス座標
		screenEnd_[i] = {};//スクリーン座標
		//線の終点↑
	}
	color = 0xFFFFFFFF;//線の色

}

Grid::~Grid() {
}

void Grid::Initialize(Camera* camera) {
	camera_ = camera;//カメラのコピー
	for (int i = 0; i < kElementCount; i++) {
		gridScale_[i] = { 1.0f,1.0f,1.0f };
		gridRotate_[i] = {};
		gridTranslate_[i] = {};
	}
}

void Grid::Update(char* keys, char* preKeys) {
	bool press_D = keys[DIK_D] && preKeys[DIK_D];
	bool press_A = keys[DIK_A] && preKeys[DIK_A];
	bool press_W = keys[DIK_W] && preKeys[DIK_W];
	bool press_S = keys[DIK_S] && preKeys[DIK_S];
	bool press_E = keys[DIK_E] && preKeys[DIK_E];
	bool press_Q = keys[DIK_Q] && preKeys[DIK_Q];
	for (int i = 0; i < kElementCount; i++) {
		gridRotate_[i] += rotateSpeed_;

		//Z座標
		if (press_D) {
			rotateSpeed_.z = kRotateSpeed;
		}
		else if (press_A) {
			rotateSpeed_.z = -kRotateSpeed;
		}
		else {
			rotateSpeed_.z = 0;
		}

		//X座標
		if (press_W) {
			rotateSpeed_.x = kRotateSpeed;
		}
		else if (press_S) {
			rotateSpeed_.x = -kRotateSpeed;
		}
		else {
			rotateSpeed_.x = 0;
		}

		//Y座標
		if (press_E) {
			rotateSpeed_.y = kRotateSpeed;
		}
		else if (press_Q) {
			rotateSpeed_.y = -kRotateSpeed;
		}
		else {
			rotateSpeed_.y = 0;
		}
	}
}

void Grid::DebugText(int i) {
	ImGui::DragFloat3("rotate", &gridRotate_[i].x,0.01f);
}

void Grid::Draw() {
	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const float kGridEvery = (kGridHalfWidth * 2.0f) / (float)kSubdivision;//1つ分の長さ

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		localStart_[xIndex].x = (-(float)kSubdivision / 2.0f + (float)xIndex) * kGridEvery;
		localStart_[xIndex].z = -kGridHalfWidth;

		locakEnd_[xIndex].x = (-(float)kSubdivision / 2.0f + (float)xIndex) * kGridEvery;
		locakEnd_[xIndex].z = kGridHalfWidth;

		Character::ScreenTransform(camera_, localStart_[xIndex], screenStart_[xIndex], gridScale_[xIndex], gridRotate_[xIndex], gridTranslate_[xIndex]);
		Character::ScreenTransform(camera_, locakEnd_[xIndex], screenEnd_[xIndex], gridScale_[xIndex], gridRotate_[xIndex], gridTranslate_[xIndex]);

		Novice::DrawLine(
			(int)screenStart_[xIndex].x, (int)screenStart_[xIndex].y,
			(int)screenEnd_[xIndex].x, (int)screenEnd_[xIndex].y,
			color
		);
		//中心だけ黒
		color = (xIndex == kSubdivision / 2 - 1) ? BLACK : 0xFFFFFF88;
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		localStart_[zIndex].z = (-(float)kSubdivision / 2.0f + (float)zIndex) * kGridEvery;
		localStart_[zIndex].x = -kGridHalfWidth;
		locakEnd_[zIndex].z = (-(float)kSubdivision / 2.0f + (float)zIndex) * kGridEvery;
		locakEnd_[zIndex].x = kGridHalfWidth;

		Character::ScreenTransform(camera_, localStart_[zIndex], screenStart_[zIndex], gridScale_[zIndex], gridRotate_[zIndex], gridTranslate_[zIndex]);
		Character::ScreenTransform(camera_, locakEnd_[zIndex], screenEnd_[zIndex], gridScale_[zIndex], gridRotate_[zIndex], gridTranslate_[zIndex]);

		Novice::DrawLine(
			(int)screenStart_[zIndex].x, (int)screenStart_[zIndex].y,
			(int)screenEnd_[zIndex].x, (int)screenEnd_[zIndex].y,
			color
		);

		//中心だけ黒
		color = (zIndex == kSubdivision / 2 - 1) ? BLACK : 0xFFFFFF88;

	}
}
