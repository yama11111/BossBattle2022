#pragma once
#include "Camera.h"
#include "Ease.h"
#include "Timer.h"

class CameraManager
{
private:
	// カメラワーク
	enum class CameraWork
	{ 
		StartCW, // start
		PlayCW, // play
		BossAttackCW,
		ClearCW, // clear
	};
	// 開始演出シーン
	enum class StartAnimeScene 
	{
		VisitAS, // 着陸
		IntroAS, // 解説
		FadeOutAS, // フェードアウト
		BirdEyeAS, // 俯瞰
		EndAS, // 終了
	};
	// プレイ時動作
	enum class PlayMovement
	{
		AdulationM, // 追従
		LookingM, // 傍観
	};
private:
	// カメラ
	Camera camera_;

	// 現在CameraWork
	CameraWork cameraWork_;
	// 現在StartAnimeScene
	StartAnimeScene startAS_;
	// 現在PlayMovement
	PlayMovement playM_;

	// 開始演出用イージング
	Math::Ease<Math::Vec3> startE_;
	// 開始演出用タイマー
	Math::Timer startT_;
	// プレイ時動作用イージング
	Math::Ease<Math::Vec3> playE_;
	// プレイ時動作用タイマー
	Math::Timer playT_;


	Math::Vec3 elderPlayerPos_;
	Math::Vec3 velocityEP_;
public:
	// 初期化
	void Initialize();
	// カメラシェイク
	void Shaking(const float swing, const float dekey);
	// trfm → vp
	void Update();
public:
	// ビュープロジェクション
	Object::ViewProjection GetViewProjection();
public:
	// 開始演出
	void ActStartAnimation() { SetStartAnimation(StartAnimeScene::VisitAS); }
private:
	// StartAnime
	void SetStartAnimation(const StartAnimeScene& anime);
	void UpdateStartAnimation();
	// PlayMovement
	void PlayMovementUpdate();
public:
	// 静的プレイヤーポインタ
	static Object::Transform* pPlayer_;
	// 静的エネミーポインタ
	static Object::Transform* pEnemy_;
public:
	// 静的初期化
	static void StaticInitialize(Object::Transform* pPlayer, Object::Transform* pEnemy);
};

