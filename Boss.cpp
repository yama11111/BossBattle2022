#include "Boss.h"

void Boss::Initalize()
{

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

}

void Boss::Attack()
{
	
}
