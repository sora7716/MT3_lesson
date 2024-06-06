#pragma once
#include <Novice.h>
#include <cmath>
#include <array>
#define _USE_MATH_DEFINES
#include "scene/func/Math.h"
#include "scene/func/ScreenPrintf.h"
#include "scene/func/Aithmetic.h"

class GameObject
{
protected://メンバ関数

	/// <summary>
	/// 倍率
	/// </summary>
	/// <param name="front">手前に来るキーを押してか?</param>
	/// <param name="behind">後ろに行くキーを押したか?</param>
	void Scale(bool front, bool behind);

	/// <summary>
	/// 回転
	/// </summary>
	void Rotate();

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="left">左に行くキーを押したか?</param>
	/// <param name="right">右に行くキーを押したか?</param>
	/// <param name="direction">進んでほしい方向</param>
	void Translate(bool left, bool right, float direction);

public:
	int windowWidth_ = 0;//横幅
	int windowHeight_ = 0;//縦幅

	MyVector3 scale_     = {};//倍率
	MyVector3 rotate_    = {};//角度
	MyVector3 translate_ = {};//ポジション
	
	Vector3   scaling_   = {};//拡縮
	Vector3   radian_    = {};//回転
	Vector3   velocity_  = {};//移動速度

};

