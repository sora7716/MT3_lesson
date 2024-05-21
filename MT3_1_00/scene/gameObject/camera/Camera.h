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
	void Update(char* keys, char* preKeys)override;

	/// <summary>
	/// 拡縮
	/// </summary>
	void Scale(char* keys, char* preKeys)override;

	/// <summary>
	/// 回転
	/// </summary>
	void Rotation()override;

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Transfer(char* keys, char* preKeys)override;

	/// <summary>
	/// レンダリングパイプライン
	/// </summary>
	void RenderingPipeline()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()override;

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

private://メンバ変数

	MyMatrix4x4 cameraMatrix_         = {};//カメラマトリックス
	MyMatrix4x4 viewMatrix_           = {};//ビューマトリックス
	MyMatrix4x4 projectionMatrix_     = {};//同次クリップ空間
	MyMatrix4x4 viewProjectionMatrix_ = {};//wvpマトリックス
	MyMatrix4x4 viewportMatrix_       = {};//ビューポートマトリックス

};

