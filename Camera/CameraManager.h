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
	// �J����
	Camera camera_;
	// �C�[�W���O�p
	Math::Ease<Math::Vec3> ease;
	// ����StartAnimeScene
	StartAnimeScene startAS_;
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
public:
	static Object::Transform* pPlayer_;
	static Object::Transform* pEnemy_;
public:
	static void StaticInitialize(Object::Transform* pPlayer, Object::Transform* pEnemy);
};

