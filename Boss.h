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
	Move,  //移動
	Attack,//攻撃
};

//enum AttackAction
//{
//	Charge,//溜め
//	Attack,//攻撃
//	End,   //終わり
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

	//敵の行動パターン用変数
	int action = Action::Move;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initalize();

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

};

