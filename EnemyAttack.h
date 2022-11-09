#pragma once
#include "Model.h"

using namespace DX;
using namespace Math;
using namespace Object;

class EnemyAttack {
public:
	Model* model;
	Transform transform;

	EnemyAttack(Transform t, Model* model);
	//~EnemyAttack();
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection& vp, const UINT tex);
	Vec3 GetWorldPosition();
	bool GetIsDied() { return IsDead; };
private:
	void Atack();
	bool IsDead = false;
};