#include "CameraManager.h"
#include "Calc.h"
#include <cassert>

Object::Transform* CameraManager::pPlayer_ = nullptr;
Object::Transform* CameraManager::pEnemy_ = nullptr;

void CameraManager::StaticInitialize(Object::Transform* pPlayer, Object::Transform* pEnemy)
{
	assert(pPlayer != nullptr);
	assert(pEnemy != nullptr);

	pPlayer_ = pPlayer;
	pEnemy_ = pEnemy;
}

void CameraManager::Initialize()
{
	camera_.Initialize({});
	ease_.Initialize({}, {}, 0, 0);
	startAS_ = StartAnimeScene::EndAS;
}

void CameraManager::Shaking(const float swing, const float dekey)
{
	camera_.Shaking(swing, dekey);
}

void CameraManager::SetStartAnimation(const StartAnimeScene& anime)
{
	startAS_ = anime;

	if (anime == StartAnimeScene::IntroAS) { return; }

	if (anime == StartAnimeScene::VisitAS)
	{
		Object::Transform::Status trfmS;
		trfmS.pos_ = { pEnemy_->pos_.x - 20.0f,10.0f,pEnemy_->pos_.z - 45.0f };
		camera_.Initialize({trfmS});
	}
	else if(anime == StartAnimeScene::FadeOutAS)
	{
		Math::Vec3 start = camera_.pos_;
		Math::Vec3 end = { pPlayer_->pos_.x - 20.0f,10.0f,pPlayer_->pos_.z - 25.0f };
		float power = 2.0f;
		float increase = 0.01f;
		ease_.Initialize(start, end, power, increase);
	}
	else if (startAS_ == StartAnimeScene::BirdEyeAS)
	{
		Math::Vec3 start = camera_.pos_;
		Math::Vec3 end = { pPlayer_->pos_.x,50.0f,pPlayer_->pos_.z - 100.0f };
		float power = 2.0f;
		float increase = 0.01f;
		ease_.Initialize(start, end, power, increase);
	}
}

void CameraManager::UpdateStartAnimation()
{
	if (startAS_ == StartAnimeScene::EndAS) { return; }

	if (startAS_ == StartAnimeScene::VisitAS)
	{
		if (pEnemy_->pos_.y == pEnemy_->scale_.y)
		{
			SetStartAnimation(StartAnimeScene::IntroAS);
			camera_.Shaking(5.0f, 0.1f);
		}
	}
	else if (startAS_ == StartAnimeScene::IntroAS)
	{
		if (!camera_.IsShake())
		{
			SetStartAnimation(StartAnimeScene::FadeOutAS);
		}
	}
	else if (startAS_ == StartAnimeScene::FadeOutAS)
	{
		ease_.Update(true);
		camera_.pos_ = ease_.Out();
		if (ease_.IsEnd())
		{
			SetStartAnimation(StartAnimeScene::BirdEyeAS);
		}
	}
	else if (startAS_ == StartAnimeScene::BirdEyeAS)
	{
		ease_.Update(true);
		camera_.pos_ = ease_.In();
		if (ease_.IsEnd())
		{
			SetStartAnimation(StartAnimeScene::EndAS);
		}
	}
	Math::Vec3 velocity = pEnemy_->pos_;
	velocity -= camera_.pos_;
	camera_.rota_ = Math::AdjustAngle(velocity);
}

void CameraManager::Update()
{
	UpdateStartAnimation();

	camera_.Update();
}

Object::ViewProjection CameraManager::GetViewProjection()
{
	return camera_.GetViewProjection();
}
