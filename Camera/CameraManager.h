#pragma once
#include "Camera.h"
#include "Ease.h"
#include "Timer.h"

class CameraManager
{
private:
	// �J�������[�N
	enum class CameraWork
	{ 
		StartCW, // start
		PlayCW, // play
		BossAttackCW,
		ClearCW, // clear
	};
	// �J�n���o�V�[��
	enum class StartAnimeScene 
	{
		VisitAS, // ����
		IntroAS, // ���
		FadeOutAS, // �t�F�[�h�A�E�g
		BirdEyeAS, // ����
		EndAS, // �I��
	};
	// �v���C������
	enum class PlayMovement
	{
		AdulationM, // �Ǐ]
		LookingM, // �T��
	};
private:
	// �J����
	Camera camera_;

	// ����CameraWork
	CameraWork cameraWork_;
	// ����StartAnimeScene
	StartAnimeScene startAS_;
	// ����PlayMovement
	PlayMovement playM_;

	// �J�n���o�p�C�[�W���O
	Math::Ease<Math::Vec3> startE_;
	// �J�n���o�p�^�C�}�[
	Math::Timer startT_;
	// �v���C������p�C�[�W���O
	Math::Ease<Math::Vec3> playE_;
	// �v���C������p�^�C�}�[
	Math::Timer playT_;


	Math::Vec3 elderPlayerPos_;
	Math::Vec3 velocityEP_;
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
	// �J�n���o
	void ActStartAnimation() { SetStartAnimation(StartAnimeScene::VisitAS); }
private:
	// StartAnime
	void SetStartAnimation(const StartAnimeScene& anime);
	void UpdateStartAnimation();
	// PlayMovement
	void PlayMovementUpdate();
public:
	// �ÓI�v���C���[�|�C���^
	static Object::Transform* pPlayer_;
	// �ÓI�G�l�~�[�|�C���^
	static Object::Transform* pEnemy_;
public:
	// �ÓI������
	static void StaticInitialize(Object::Transform* pPlayer, Object::Transform* pEnemy);
};

