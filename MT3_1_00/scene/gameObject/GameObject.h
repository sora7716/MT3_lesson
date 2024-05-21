#pragma once
#include <Novice.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include "scene/func/Math.h"
#include "scene/func/ScreenPrintf.h"
#include "scene/func/Aithmetic.h"

class GameObject
{
protected://メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	virtual void Update(char*keys,char*preKeys);
	
	/// <summary>
	/// 拡縮
	/// </summary>
	virtual void Scale(char* keys, char* preKeys);

	/// <summary>
	/// 回転
	/// </summary>
	virtual void Rotation();

	/// <summary>
	/// レンダリングパイプライン
	/// </summary>
	virtual void RenderingPipeline();

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	virtual void Transfer(char*keys,char*preKeys);

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();

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

