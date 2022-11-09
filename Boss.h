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
	Move,  //Ú®
	Attack,//U
};

enum AttackAction
{
	NonePhase,
	AttackPhase,//U
	ChargePhase,//­ß
	EndPhase,   //Iíè
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

	//GÌs®p^[pÏ
	int action = Action::Move;
	int attackAction = AttackAction::NonePhase;
public:
	
	/// <summary>
	/// ú»
	/// </summary>
	void Initalize(Model*model);

	/// <summary>
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// `æ
	/// </summary>
	void Draw();

	/// <summary>
	/// Ú®
	/// </summary>
	void Move();

	/// <summary>
	/// U
	/// </summary>
	void Attack();

	/// <summary>
	/// posÌQb^[
	/// </summary>
	/// <returns></returns>
	Vec3 GetWorldPosition();

};

