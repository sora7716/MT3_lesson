#pragma once
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
	/// レンダリングパイプライン
	/// </summary>
	void RenderingPipeline();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// ビュープロジェクションマトリックスのゲッター
	/// </summary>
	/// <returns></returns>
	MyMatrix4x4 GetViewProjectionMatrix() { return viewProjectionMatrix_; };

	/// <summary>
	/// ビューポートマトリックスのゲッター
	/// </summary>
	/// <returns></returns>
	MyMatrix4x4 GetViewportMatrix() { return viewportMatrix_; };

	/// <summary>
	/// scale_のゲッター
	/// </summary>
	/// <returns></returns>
	MyVector3 GetScale() { return scale_; };

	/// <summary>
	/// rotate_のゲッター
	/// </summary>
	/// <returns></returns>
	MyVector3 GetRotate() { return rotate_; };

	/// <summary>
	/// translate_のゲッター
	/// </summary>
	/// <returns></returns>
	MyVector3 GetTranslate() { return translate_; };

public://メンバ変数

	MyMatrix4x4 cameraMatrix_         = {};//カメラマトリックス
	MyMatrix4x4 viewMatrix_           = {};//ビューマトリックス
	MyMatrix4x4 projectionMatrix_     = {};//同次クリップ空間
	MyMatrix4x4 viewProjectionMatrix_ = {};//wvpマトリックス
	MyMatrix4x4 viewportMatrix_       = {};//ビューポートマトリックス

};

