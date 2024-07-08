﻿#pragma once
#include "scene/gameObject/GameObject.h"
class Camera:public GameObject{

public://メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="kWindowWidth"></param>
	/// <param name="kWindowHeight"></param>
	void Initialize(int kWindowWidth, int kWindowHeight);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Update(char* keys, char* preKeys);

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// ビュープロジェクションマトリックスのゲッター
	/// </summary>
	/// <returns></returns>
	Matrix4x4 GetViewProjectionMatrix();

	/// <summary>
	/// ビューポートマトリックスのゲッター
	/// </summary>
	/// <returns></returns>
	Matrix4x4 GetViewportMatrix();

	/// <summary>
	/// scale_のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetScale();

	/// <summary>
	/// rotate_のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetRotate();

	/// <summary>
	/// translate_のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetTranslate();

private://メンバ変数

	Matrix4x4 cameraMatrix_         = {};//カメラマトリックス
	Matrix4x4 viewMatrix_           = {};//ビューマトリックス
	Matrix4x4 projectionMatrix_     = {};//同次クリップ空間
	Matrix4x4 viewProjectionMatrix_ = {};//wvpマトリックス
	Matrix4x4 viewportMatrix_       = {};//ビューポートマトリックス

private://メンバ変数
	/// <summary>
	/// レンダリングパイプライン
	/// </summary>
	void RenderingPipeline();
};

