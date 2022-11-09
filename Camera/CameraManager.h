#pragma once
#include "Camera.h"
#include "Ease.h"

class CameraManager
{
private:
	enum class CameraWork
	{ 
		StartCW,
		PlayCW,
		BossAttackCW,
		ClearCW,
	};
	enum class StartAnimeScene 
	{
		VisitAS,
		IntroAS,
		FadeOutAS,
		BirdEyeAS,
		EndAS,
	};
	enum class PlayMovement
	{
		AdulationM,
		LookingM,
	};
private:
	// カメラ
	Camera camera_;
	// 現在CameraWork
	CameraWork cameraWork_;
	// 現在StartAnimeScene
	StartAnimeScene startAS_;
	// イージング用
	Math::Ease<Math::Vec3> startEase_;
	// 現在PlayMovement
	PlayMovement playM_;
	// イージング用
	Math::Ease<Math::Vec3> playEase_;

	
	Math::Vec3 vel;

	Math::Vec3 elderPlayerPos_;
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
	void ActStartAnimation() { SetStartAnimation(StartAnimeScene::VisitAS); }
private:
	// StartAnime
	void SetStartAnimation(const StartAnimeScene& anime);
	void UpdateStartAnimation();
	// PlayMovement
	void PlayMovementUpdate();
public:
	static Object::Transform* pPlayer_;
	static Object::Transform* pEnemy_;
public:
	static void StaticInitialize(Object::Transform* pPlayer, Object::Transform* pEnemy);
};

