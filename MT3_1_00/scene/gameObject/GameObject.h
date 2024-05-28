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
	/// <param name="front"></param>
	/// <param name="preFront"></param>
	/// <param name="behind"></param>
	/// <param name="preBehind"></param>
	void Scale(char front, char preFront, char behind, char preBehind);

	/// <summary>
	/// 回転
	/// </summary>
	void Rotate();

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="left"></param>
	/// <param name="preLeft"></param>
	/// <param name="right"></param>
	/// <param name="preRight"></param>
	/// <param name="direction"></param>
	void Translate(char left, char preLeft, char right, char preRight, float direction);

protected:
	int windowWidth_ = 0;//横幅
	int windowHeight_ = 0;//縦幅

	MyVector3 scale_     = {};//倍率
	MyVector3 rotate_    = {};//角度
	MyVector3 translate_ = {};//ポジション
	
	Vector3   scaling_   = {};//拡縮
	Vector3   radian_    = {};//回転
	Vector3   velocity_  = {};//移動速度

};

