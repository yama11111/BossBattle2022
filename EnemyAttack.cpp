#include "EnemyAttack.h"

EnemyAttack::EnemyAttack(Transform t, Model* model) {

	transform.Initialize({ });

	transform = t;

	this->model = model;
}

Vec3 EnemyAttack::GetWorldPosition() {
	Vec3 worldPos;

	worldPos.x = transform.pos_.x;
	worldPos.y = transform.pos_.y;
	worldPos.z = transform.pos_.z;

	return worldPos;
}

void EnemyAttack::Initialize(Model* model) {

	this->model = model;

	transform.Initialize({ });
}

void EnemyAttack::Update() {

	//スピード
	const float speed = 0.3f;

	transform.Update();
}

void EnemyAttack::Draw(ViewProjection& vp, const UINT tex) {
	model->Draw(transform, vp, tex);
}

void EnemyAttack::Atack() {

}