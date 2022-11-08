#pragma once
#include "Camera.h"
#include "Ease.h"

class CameraManager
{
private:
	enum class StartAnimeScene 
	{
		VisitAS,
		IntroAS,
		FadeOutAS,
		EndAS,
	};
private:
	// カメラ
	Camera camera_;
	// イージング用
	Math::Ease<Math::Vec3> ease;
	// 現在StartAnimeScene
	StartAnimeScene startAS_;
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
public:
	static Object::Transform* pPlayer_;
	static Object::Transform* pEnemy_;
public:
	static void StaticInitialize(Object::Transform* pPlayer, Object::Transform* pEnemy);
};

