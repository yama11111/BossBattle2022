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
	startEase_.Initialize({}, {}, 0, 0);
	playEase_.Initialize({}, {}, 0, 0);
	cameraWork_ = CameraWork::StartCW;
	startAS_ = StartAnimeScene::VisitAS;
	playM_ = PlayMovement::AdulationM;
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
		cameraWork_ = CameraWork::StartCW;
	}
	else if(anime == StartAnimeScene::FadeOutAS)
	{
		Math::Vec3 start = camera_.pos_;
		Math::Vec3 end = { pPlayer_->pos_.x - 20.0f,10.0f,pPlayer_->pos_.z - 25.0f };
		float power = 2.0f;
		float increase = 0.01f;
		startEase_.Initialize(start, end, power, increase);
	}
	else if (startAS_ == StartAnimeScene::BirdEyeAS)
	{
		Math::Vec3 start = camera_.pos_;
		Math::Vec3 end = { pPlayer_->pos_.x,50.0f,pPlayer_->pos_.z - 100.0f };
		float power = 2.0f;
		float increase = 0.01f;
		startEase_.Initialize(start, end, power, increase);
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
		startEase_.Update(true);
		camera_.pos_ = startEase_.Out();
		if (startEase_.IsEnd())
		{
			SetStartAnimation(StartAnimeScene::BirdEyeAS);
		}
	}
	else if (startAS_ == StartAnimeScene::BirdEyeAS)
	{
		startEase_.Update(true);
		camera_.pos_ = startEase_.In();
		if (startEase_.IsEnd())
		{
			SetStartAnimation(StartAnimeScene::EndAS);
			cameraWork_ = CameraWork::PlayCW;
			Math::Vec3 back = pPlayer_->pos_;
			Math::Vec3 v = vel;
			v *= 1.25;
			back -= v;

			back.y *= -1;
			back.y += 25;


			playEase_.Initialize(camera_.pos_, back, 2.0f, 0.05f);

		}
	}
}

void CameraManager::PlayMovementUpdate()
{
	float length = vel.Length();

	if (true)
	{
		playM_ = PlayMovement::AdulationM;
	}
	else
	{
		playM_ = PlayMovement::LookingM;
	}


	if (playM_ == PlayMovement::AdulationM)
	{
		if (elderPlayerPos_.x != pPlayer_->pos_.x ||
			elderPlayerPos_.z != pPlayer_->pos_.z)
		{
			Math::Vec3 back = pPlayer_->pos_;
			Math::Vec3 v = vel;
			v *= 1.25;
			back -= v;

			back.y *= -1;
			back.y += 25;

			if (playEase_.IsEnd())
			{
				//playEase_.Initialize(camera_.pos_, back, 2.0f, 0.05f);
				playEase_.SetEnd(back);
			}
			else
			{
				playEase_.SetEnd(back);
			}
		}

	}
	else if (playM_ == PlayMovement::LookingM)
	{

	}

	elderPlayerPos_ = pPlayer_->pos_;

	playEase_.Update(true);

	camera_.pos_ = playEase_.In();

}

void CameraManager::Update()
{
	vel = pEnemy_->pos_;
	vel -= pPlayer_->pos_;
	vel.Normalized();

	if (cameraWork_ == CameraWork::StartCW)
	{
		UpdateStartAnimation();
	}
	else if (cameraWork_ == CameraWork::PlayCW)
	{
		PlayMovementUpdate();
	}

	Math::Vec3 velocity = pEnemy_->pos_;
	velocity -= camera_.pos_;
	camera_.rota_ = Math::AdjustAngle(velocity);

	camera_.Update();
}

Object::ViewProjection CameraManager::GetViewProjection()
{
	return camera_.GetViewProjection();
}
