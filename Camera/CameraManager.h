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
		KamikazeCW, // special attack
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
	// �P�����o�V�[��
	enum class KamikazeAnimeScene
	{
		FlyAS, // ����
		ObservationAS, // ���
		WarningAS, // ����
		AttackAS, // �P��
		EndAS, // �I��
	};
private:
	// �J����
	Camera camera_;
	// �Ǐ]�t���O
	bool isAdulation = false;

	// ����CameraWork
	CameraWork cameraWork_;
	// ����StartAnimeScene
	StartAnimeScene startAS_;
	// ����PlayMovement
	PlayMovement playM_;
	// ����KamikazeAnimeScene
	KamikazeAnimeScene kamikazeAS_;

	// �J�n���o�p�C�[�W���O
	Math::Ease<Math::Vec3> startE_;
	// �J�n���o�p�^�C�}�[
	Math::Timer startT_;

	// �v���C������p�C�[�W���O
	Math::Ease<Math::Vec3> playE_;
	// �v���C������p�^�C�}�[
	Math::Timer playT_;

	// �P�����o�p�C�[�W���O
	Math::Ease<Math::Vec3> kamikazeE_;
	// �P�����o�p�^�C�}�[
	Math::Timer kamikazeT_;
	// �P�����o�p�C�[�W���O
	Math::Ease<Math::Vec3> kamikazeE2_;
	// �P�����o�p�^�C�}�[
	Math::Timer kamikazeT2_;

	int ttt = 0;

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
	// �J��������
	Math::Vec3 CameraVelocity();
public:
	// �J�n���o
	void ActStartAnimation() { SetStartAnimation(StartAnimeScene::VisitAS); }
	// �K�E���o
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
	// �ÓI�v���C���[�|�C���^
	static Object::Transform* pPlayer_;
	// �ÓI�G�l�~�[�|�C���^
	static Object::Transform* pEnemy_;
public:
	// �ÓI������
	static void StaticInitialize(Object::Transform* pPlayer, Object::Transform* pEnemy);
};

