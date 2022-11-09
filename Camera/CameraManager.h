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
	// �J����
	Camera camera_;
	// ����CameraWork
	CameraWork cameraWork_;
	// ����StartAnimeScene
	StartAnimeScene startAS_;
	// �C�[�W���O�p
	Math::Ease<Math::Vec3> startEase_;
	// ����PlayMovement
	PlayMovement playM_;
	// �C�[�W���O�p
	Math::Ease<Math::Vec3> playEase_;

	
	Math::Vec3 vel;

	Math::Vec3 elderPlayerPos_;
public:
	// ������
	void Initialize();
	// �J�����V�F�C�N
	void Shaking(const float swing, const float dekey);
	// trfm �� vp
	void Update();
public:
	// �r���[�v���W�F�N�V����
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

