#pragma once
#include <Novice.h>
#include <cmath>
#include <array>
#define _USE_MATH_DEFINES
#include <ImGui.h>
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
	/// X座標の移動
	/// </summary>
	/// <param name="bottom1">左に行くキーを押したか?</param>
	/// <param name="bottom2">右に行くキーを押したか?</param>
	/// <param name="type">カメラだったら-1,それ以外は1を入れる</param>
	void TranslateX(bool bottom1, bool bottom2, float type);

	/// <summary>
	/// Y座標の移動
	/// </summary>
	/// <param name="bottom1">上に行くボタン</param>
	/// <param name="bottom2">下に行くボタン</param>
	/// <param name="type">カメラだったら-1,それ以外は1を入れる</param>
	void TranslateY(bool bottom1, bool bottom2, float type);

	/// <summary>
	/// Z座標の移動
	/// </summary>
	/// <param name="bottom1">前に行く</param>
	/// <param name="bottom2">後ろに行く</param>
	/// <param name="type">カメラだったら-1,それ以外は1を入れる</param>
	void TranslateZ(bool bottom1, bool bottom2, float type);

	/// <summary>
	/// 移動をまとめた
	/// </summary>
	/// <param name="left">左</param>
	/// <param name="right">右</param>
	/// <param name="up">上</param>
	/// <param name="down">下</param>
	/// <param name="front">前</param>
	/// <param name="behind">後ろ</param>
	/// <param name="type"></param>
	void Movement(bool left, bool right, bool up, bool down, bool front, bool behind, float type);

protected:
	int windowWidth_ = 0;//横幅
	int windowHeight_ = 0;//縦幅

	Vector3 scale_     = {};//倍率
	Vector3 rotate_    = {};//角度
	Vector3 translate_ = {};//ポジション
	
	Vector3   scaling_   = {};//拡縮
	Vector3   radian_    = {};//回転
	Vector3   velocity_  = {};//移動速度

};

