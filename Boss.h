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
	Move,  //移動
	Attack,//攻撃
};

enum AttackAction
{
	NonePhase,
	AttackPhase,//攻撃
	ChargePhase,//溜め
	EndPhase,   //終わり
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

	//敵の行動パターン用変数
	int action = Action::Move;
	int attackAction = AttackAction::NonePhase;
public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initalize(Model*model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// posのゲッター
	/// </summary>
	/// <returns></returns>
	Vec3 GetWorldPosition();

};

