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

public://構造体など

	//ベクトル2の整数型
	typedef struct Vector2Int {
		int x;
		int y;
	}Vector2Int;

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
	/// X座標の回転
	/// </summary>
	/// <param name="bottom1"></param>
	/// <param name="bottom2"></param>
	void RotateX(bool bottom1, bool bottom2);

	/// <summary>
	/// Y座標の回転
	/// </summary>
	/// <param name="bottom1"></param>
	/// <param name="bottom2"></param>
	void RotateY(bool bottom1, bool bottom2);

	/// <summary>
	/// Z座標の回転
	/// </summary>
	/// <param name="bottom1"></param>
	/// <param name="bottom2"></param>
	void RotateZ(bool bottom1, bool bottom2);

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

	/// <summary>
	/// 回転をまとめた
	/// <param name="left">左</param>
	/// <param name="right">右</param>
	/// <param name="up">上</param>
	/// <param name="down">下</param>
	/// <param name="front">前</param>
	/// <param name="behind">後ろ</param>
	void Rotation(bool left, bool right, bool up, bool down, bool front, bool behind);

	/// <summary>
	/// 拡大縮小
	/// </summary>
	void Scaling();

	/// <summary>
	/// 回転
	/// </summary>
	void Rotation();

protected:
	int windowWidth_ = 0;//横幅
	int windowHeight_ = 0;//縦幅

	Vector3 scale_ = {};//倍率
	Vector3 rotate_ = {};//角度
	Vector3 translate_ = {};//ポジション

	Vector3   scaling_ = {};//拡縮
	Vector3   radian_ = {};//回転
	Vector3   velocity_ = {};//移動速度

	Vector2Int mousePos_ = {};//マウスのポジション
	Vector2Int preMousePos_ = {};//前のマウスのポジション
};

