#include "Enemy.h"

Enemy::~Enemy() {
	for (int i = 0; i < enemyAttack.size(); i++)
	{
		delete enemyAttack[i];
	}
}

Vec3 Enemy::GetWorldPosition() {
	Vec3 worldPos;

	worldPos.x = transform.pos_.x;
	worldPos.y = transform.pos_.y;
	worldPos.z = transform.pos_.z;

	return worldPos;
}

void Enemy::Initialize(Model* model) {

	time = 0;

	this->model = model;

	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	transform.Initialize({ });

	transform.pos_.x = 10.0f;

	enemyAttack.clear();
}

void Enemy::Update() {

	//�X�s�[�h
	const float speed = 0.3f;

	/*if (key->IsDown(DIK_W)) {
		transform.pos_.z += speed;
	};
	if (key->IsDown(DIK_S)) {
		transform.pos_.z -= speed;
	};

	if (key->IsDown(DIK_D)) {
		transform.pos_.x += speed;
	};
	if (key->IsDown(DIK_A)) {
		transform.pos_.x -= speed;
	};

	if (key->IsDown(DIK_E)) {
		transform.pos_.y += speed;
	};
	if (key->IsDown(DIK_Q)) {
		transform.pos_.y -= speed;
	};*/

	//�W�����v
	Jump();

	////�͈͂𒴂��Ȃ�����
	transform.pos_.y = max(transform.pos_.y, -kMoveLimitY);
	transform.pos_.y = min(transform.pos_.y, +kMoveLimitY);
	transform.pos_.x = max(transform.pos_.x, -kMoveLimitX);
	transform.pos_.x = min(transform.pos_.x, +kMoveLimitX);
	transform.pos_.z = max(transform.pos_.z, -kMoveLimitZ);
	transform.pos_.z = min(transform.pos_.z, +kMoveLimitZ);

	//key->Update();
	transform.Update();

	for (int i = 0; i < enemyAttack.size(); i++)
	{
		enemyAttack[i]->Update();

		if (enemyAttack[i]->GetIsDied())
		{
			enemyAttack.erase(enemyAttack.begin() + i);
		}
	}
}

void Enemy::Draw(ViewProjection& vp, const UINT tex,const UINT tex2) {
	model->Draw(transform, vp, tex);

	for (int i = 0; i < enemyAttack.size(); i++)
	{
		enemyAttack[i]->Draw(vp,tex2);
	}
}

void Enemy::Jump() {
	/*if (key->IsTrigger(DIK_Z)) {

		if (transform.pos_.y < -kMoveLimitY + 1) {

			Gravity = 0;

			jump = Maxjump;

			jumpCount = 0;
		}
	}*/

	//�W�����v
	if (Gravity < MaxGravity) {
		Gravity += 0.02f;
	}

	if (jump > 0) {
		transform.pos_.y += jump;

		jump -= 0.1f;
	}
	else {
		transform.pos_.y -= Gravity;
	}
}

void Enemy::Atack() {
		//�����̒��g�����
		EnemyAttack* newenemyAttack = new EnemyAttack(transform,model);
		//�i�[
		enemyAttack.push_back(newenemyAttack);
}

void Enemy::Avoidance() {

}