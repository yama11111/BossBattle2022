#include "EnemyAttack.h"

EnemyAttack::EnemyAttack(Vec3 t, Model* model) {

	transform.pos_ = t;

	speed = 1.0f;

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

	if (transform.pos_.y < 20) {
		transform.pos_.y++;
	}else {
		transform.pos_.z -= speed;
	}

	speed += 0.05f;

	const float ti = 1.0f;
	if(transform.pos_.z < -160)
		transform.scale_ -= {ti, ti, ti};

	if (transform.scale_.x < 0.1f)
		IsDead = true;

	transform.Update();
}

void EnemyAttack::Draw(ViewProjection& vp, const UINT tex) {
	model->Draw(transform, vp, tex);
}

void EnemyAttack::Atack() {

}