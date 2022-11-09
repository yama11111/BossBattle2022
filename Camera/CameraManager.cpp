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

	cameraWork_ = CameraWork::StartCW;
	startAS_ = StartAnimeScene::VisitAS;
	playM_ = PlayMovement::AdulationM;

	startE_.Initialize({}, {}, 0);
	startT_.Initialize(0);

	playE_.Initialize({}, {}, 0);
	playT_.Initialize(0);
}

void CameraManager::Shaking(const float swing, const float dekey)
{
	camera_.Shaking(swing, dekey);
}

void CameraManager::SetStartAnimation(const StartAnimeScene& anime)
{
	startAS_ = anime;

	// 解説
	if (anime == StartAnimeScene::IntroAS) { return; }
	// 終了
	if (anime == StartAnimeScene::EndAS) { return; }

	// 着陸
	if (anime == StartAnimeScene::VisitAS)
	{
		Object::Transform::Status trfmS;
		trfmS.pos_ =
		{
			pEnemy_->pos_.x - 20.0f,
			10.0f,
			pEnemy_->pos_.z - 45.0f
		};
		camera_.Initialize({trfmS});
		//カメラワーク←開始演出
		cameraWork_ = CameraWork::StartCW;
	}
	// フェードアウト
	else if(anime == StartAnimeScene::FadeOutAS)
	{
		Math::Vec3 start = camera_.pos_;
		Math::Vec3 end = 
		{
			pPlayer_->pos_.x - 20.0f,
			10.0f,
			pPlayer_->pos_.z - 25.0f 
		};
		float power = 2.0f;
		startE_.Initialize(start, end, power);

		int time = 100;
		startT_.Initialize(time);
		startT_.SetActive(true);
	}
	// 俯瞰
	else if (startAS_ == StartAnimeScene::BirdEyeAS)
	{
		Math::Vec3 start = camera_.pos_;
		Math::Vec3 end = 
		{
			pPlayer_->pos_.x,
			50.0f,
			pPlayer_->pos_.z - 100.0f 
		};
		float power = 2.0f;
		startE_.Initialize(start, end, power);

		int time = 100;
		startT_.Initialize(time);
		startT_.SetActive(true);
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
		startT_.Update();
		camera_.pos_ = startE_.Out(startT_.Ratio());
		if (startT_.IsEnd())
		{
			SetStartAnimation(StartAnimeScene::BirdEyeAS);
		}
	}
	else if (startAS_ == StartAnimeScene::BirdEyeAS)
	{
		startT_.Update();
		camera_.pos_ = startE_.In(startT_.Ratio());
		if (startT_.IsEnd())
		{
			SetStartAnimation(StartAnimeScene::EndAS);
			cameraWork_ = CameraWork::PlayCW;

			Math::Vec3 back = pPlayer_->pos_ - (velocityEP_ * 100.0f);
			back.y += 25;

			playE_.Initialize(camera_.pos_, back, 2.0f);
			playT_.Initialize(20);
			playT_.SetActive(true);
		}
	}
}

void CameraManager::PlayMovementUpdate()
{
	//float length = velocityEP_.Length();

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
			Math::Vec3 back = pPlayer_->pos_ - (velocityEP_ * 100.0f);
			back.y += 25;

			playE_.Initialize(camera_.pos_, back, 2.0f);
		}

	}
	else if (playM_ == PlayMovement::LookingM)
	{

	}

	elderPlayerPos_ = pPlayer_->pos_;

	playT_.Update();
	camera_.pos_ = playE_.In(playT_.Ratio());
}

void CameraManager::Update()
{
	velocityEP_ = pEnemy_->pos_ - pPlayer_->pos_;
	velocityEP_ = velocityEP_.Normalized();

	if (cameraWork_ == CameraWork::StartCW)
	{
		UpdateStartAnimation();
	}
	else if (cameraWork_ == CameraWork::PlayCW)
	{
		PlayMovementUpdate();
	}

	Math::Vec3 velocityEC = pEnemy_->pos_ - camera_.pos_;
	camera_.rota_ = Math::AdjustAngle(velocityEC);

	camera_.Update();
}

Object::ViewProjection CameraManager::GetViewProjection()
{
	return camera_.GetViewProjection();
}

Math::Vec3 CameraManager::CameraVelocity()
{
	return camera_.Verocity();
}
