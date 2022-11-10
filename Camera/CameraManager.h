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
		KamikazeCW, // special attack
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
	// 襲撃演出シーン
	enum class KamikazeAnimeScene
	{
		FlyAS, // 飛翔
		ObservationAS, // 解説
		WarningAS, // 俯瞰
		AttackAS, // 襲撃
		EndAS, // 終了
	};
private:
	// カメラ
	Camera camera_;
	// 追従フラグ
	bool isAdulation = false;

	// 現在CameraWork
	CameraWork cameraWork_;
	// 現在StartAnimeScene
	StartAnimeScene startAS_;
	// 現在PlayMovement
	PlayMovement playM_;
	// 現在KamikazeAnimeScene
	KamikazeAnimeScene kamikazeAS_;

	// 開始演出用イージング
	Math::Ease<Math::Vec3> startE_;
	// 開始演出用タイマー
	Math::Timer startT_;

	// プレイ時動作用イージング
	Math::Ease<Math::Vec3> playE_;
	// プレイ時動作用タイマー
	Math::Timer playT_;

	// 襲撃演出用イージング
	Math::Ease<Math::Vec3> kamikazeE_;
	// 襲撃演出用タイマー
	Math::Timer kamikazeT_;
	// 襲撃演出用イージング
	Math::Ease<Math::Vec3> kamikazeE2_;
	// 襲撃演出用タイマー
	Math::Timer kamikazeT2_;

	int ttt = 0;

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
	// カメラ向き
	Math::Vec3 CameraVelocity();
public:
	// 開始演出
	void ActStartAnimation() { SetStartAnimation(StartAnimeScene::VisitAS); }
	// 必殺演出
	void ActKamikazeAnimation() { SetKamikazeAnimation(KamikazeAnimeScene::FlyAS); }
private:
	// StartAnime
	void SetStartAnimation(const StartAnimeScene& anime);
	void UpdateStartAnimation();
	// PlayMovement
	void PlayMovementUpdate();
	// KamikazeAnime
	void SetKamikazeAnimation(const KamikazeAnimeScene& anime);
	void UpdateKamikazeAnimation();
public:
	// 静的プレイヤーポインタ
	static Object::Transform* pPlayer_;
	// 静的エネミーポインタ
	static Object::Transform* pEnemy_;
public:
	// 静的初期化
	static void StaticInitialize(Object::Transform* pPlayer, Object::Transform* pEnemy);
};

