#pragma once
#include "Model.h"
#include "Keys.h"

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Object;

class Player {
public:
	Model* model;
	Model* Attackmodel;
	Transform transform;
	Transform attack;
	Keys* key;

	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection& vp, const UINT tex, const UINT tex2);
	Vec3 GetWorldPosition();

private:
	float Gravity = 0;
	float MaxGravity = 1.0f;

	float jump = 0;
	float Maxjump = 2.5;
	int jumpCount = 0;

	bool AttackF = false;

	//ˆÚ“®ŒÀŠE
	const float kMoveLimitX = 160 - 5;
	const float kMoveLimitZ = 160 - 5;
	const float kMoveLimitY = 20;

	//ƒWƒƒƒ“ƒv,UŒ‚,‰ñ”ğ
	void Jump();
	void Attack();
	void Avoidance();
};
