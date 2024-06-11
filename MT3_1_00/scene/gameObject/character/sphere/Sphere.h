#pragma once
#include "scene/gameObject/character/Character.h"

class Camera;//前方宣言

class Sphere:Character{

public://メンバ関数
	void Initialize(Camera *camera);

	void Update();

	void DebugText();

	void Draw();

private://メンバ変数

	Vector3 center_ = {};

	float radius_ = 0;

	Camera *camera_ = nullptr;

	Vector3 screenA_= {};//スクリーン座標
	Vector3 screenB_ = {};//スクリーン座標
	Vector3 screenC_ = {};//スクリーン座標

};

