#pragma once
#include "Model.h"
#include "Keys.h"
#include "EnemyAttack.h"

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Object;

class Enemy {
public:
	Model* model;
	Transform transform;
	Keys* key;

	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection& vp, const UINT tex, const UINT tex2);
	Vec3 GetWorldPosition();

	~Enemy();

	std::vector<EnemyAttack*> getEnemyAttack;

	std::vector<EnemyAttack*> enemyAttack;
private:
	float Gravity = 0;
	float MaxGravity = 1.0f;

	float jump = 0;
	float Maxjump = 2.5;
	int jumpCount = 0;

	int time;

	//r = sin(3.1415f * 2 / 240 * time);

	//ˆÚ“®ŒÀŠE
	const float kMoveLimitX = 48;
	const float kMoveLimitZ = 48;
	const float kMoveLimitY = 20;

	void Jump();
	void Attack();
	void Avoidance();
};
