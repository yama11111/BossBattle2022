#pragma once
#include <random>

#include "Model.h"
#include "Vec3.h"

#include "Player.h"

using namespace DX;
//using namespace Input;
using namespace Math;
using namespace Object;

enum Action
{
	Move,  //�ړ�
	Attack,//�U��
};

//enum AttackAction
//{
//	Charge,//����
//	Attack,//�U��
//	End,   //�I���
//};

enum AttackValue
{
	None,
	Sky,
	Ground,

};

class Boss
{
private:
	Model model;
	Transform trasform;

	Vec3 distance = {};

	Player* player = nullptr;

	//�G�̍s���p�^�[���p�ϐ�
	int action = Action::Move;

public:
	
	/// <summary>
	/// ������
	/// </summary>
	void Initalize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

};

