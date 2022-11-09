#pragma once
#include <cassert>
#include <random>

#include "Model.h"

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

enum AttackAction
{
	NonePhase,
	AttackPhase,//�U��
	ChargePhase,//����
	EndPhase,   //�I���
};

enum AttackValue
{
	None,
	Sky,
	Ground,

};

class Boss
{
private:
	Model* model = nullptr;
	Transform transform;
	TextureManager* texture = nullptr;

	Vec3 distance = {};

	Player* player = nullptr;

	//�G�̍s���p�^�[���p�ϐ�
	int action = Action::Move;
	int attackAction = AttackAction::NonePhase;
public:
	
	/// <summary>
	/// ������
	/// </summary>
	void Initalize(Model*model);

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

	/// <summary>
	/// pos�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	Vec3 GetWorldPosition();

};

