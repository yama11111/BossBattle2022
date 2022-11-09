#include "Boss.h"

void Boss::Initalize(Model* model)
{
	assert(model);
	this->model = model;

	

	transform.Initialize({});
}

void Boss::Update()
{
	switch (action)
	{
	case Action::Move:
		Move();
		break;
	case Action::Attack:
		Attack();
		break;
	}
}

void Boss::Draw()
{

}

void Boss::Move()
{
	player->
}

void Boss::Attack()
{
	switch (attackAction)
	{
	case AttackAction::ChargePhase:
		break;
	case AttackAction::AttackPhase:
		break;
	case AttackAction::EndPhase:
		attackAction = AttackAction::NonePhase;
		break;
	}
}

Vec3 Boss::GetWorldPosition()
{
	Vec3 worldPositon;

	worldPositon.x = transform.pos_.x;
	worldPositon.y = transform.pos_.y;
	worldPositon.z = transform.pos_.z;

	return worldPositon;
}
