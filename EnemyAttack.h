#pragma once
#include "Model.h"
#include "Player.h"

using namespace DX;
using namespace Math;
using namespace Object;

class EnemyAttack {
public:
	Model* model;
	Transform transform;

	EnemyAttack(Vec3 t, Model* model);
	//~EnemyAttack();
	void Initialize(Model* model);
	void Update(Player player);
	void Draw(ViewProjection& vp, const UINT tex);
	Vec3 GetWorldPosition();
	bool GetIsDied() { return IsDead; };
private:
	void Atack();
	bool IsDead = false;
	//スピード
	float speed = 1.0f;
};