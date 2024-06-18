#pragma once
#include "scene/gameObject/character/Character.h"

class Camera;//前方宣言

class Sphere:Character{

public://メンバ関数
	typedef struct Material {
		Vector3 center;
		float radius;
	}Material;
	void Initialize(Camera *camera, Material sphere);

	void Update();

	void DebugText();

	void Draw();

private://メンバ変数
	
	Material sphere_ = {};//スフィアの素材

	Camera *camera_ = nullptr;//カメラ

	Vector3 screenA_= {};//スクリーン座標
	Vector3 screenB_ = {};//スクリーン座標
	Vector3 screenC_ = {};//スクリーン座標

};

