#include "Enemy.h"
#include <random>

int GetRandom(int min, int max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);
}

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

	IsDead = false;

	key = Keys::GetInstance();

	time = 0;

	this->model = model;

	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	transform.Initialize({ });

	transform.pos_.x = 10.0f;
	transform.pos_.z = 10.0f;

	transform.scale_ = { 10.0f,10.0f,10.0f };

	enemyAttack.clear();
}

void Enemy::Update(Player player) {

	//スピード
	const float speed = 0.3f;

	if (key->IsTrigger(DIK_T)) {
		Attack();
	}

	time++;

	int a = 100;

	if (time < 100) {
		transform.pos_.x = a;
		transform.pos_.z = a;
	}
	else if (time < 200) {
		transform.pos_.x = -a;
		transform.pos_.z = a;
	}
	else if (time < 300) {
		transform.pos_.x = a;
		transform.pos_.z = -a;
	}
	else if (time < 400) {
		transform.pos_.x = -a;
		transform.pos_.z = -a;
	}
	else {
		time = 0;
	}

	//ジャンプ
	Jump();

	////範囲を超えない処理
	/*transform.pos_.y = min(transform.pos_.y, kMoveLimitY * 3);
	transform.pos_.y = max(transform.pos_.y, +kMoveLimitY);
	transform.pos_.x = max(transform.pos_.x, -kMoveLimitX);
	transform.pos_.x = min(transform.pos_.x, +kMoveLimitX);
	transform.pos_.z = max(transform.pos_.z, -kMoveLimitZ);
	transform.pos_.z = min(transform.pos_.z, +kMoveLimitZ);*/

	//key->Update();
	transform.Update();

	for (int i = 0; i < enemyAttack.size(); i++)
	{
		enemyAttack[i]->Update(player);
	}

	for (int i = 0; i < enemyAttack.size(); i++) {
		if (enemyAttack[i]->GetIsDied())
		{
			enemyAttack.erase(enemyAttack.begin() + i);
		}
	}
}

void Enemy::Draw(ViewProjection& vp, const UINT tex, const UINT tex2) {

	if (IsDead != true)
		model->Draw(transform, vp, tex);

	for (int i = 0; i < enemyAttack.size(); i++)
	{
		enemyAttack[i]->Draw(vp, tex2);
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

	//ジャンプ
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

void Enemy::Attack() {

	int a = GetRandom(0, 7);

	for (int i = 0; i < 8; i++)
	{
		if (i == a) {
			i++;
			if (i > 7)
				break;
		}

		//仮沖の中身を作る
		EnemyAttack* newenemyAttack = new EnemyAttack(transform.pos_, model);

		newenemyAttack->transform.Initialize({});

		newenemyAttack->transform.scale_ = { 20.0f,20.0f,20.0f };

		Vec4 a = { 0.5f,0.0f,0.0f,1.0f };

		newenemyAttack->transform.SetColor(a);

		newenemyAttack->transform.pos_ = {
			((newenemyAttack->transform.scale_.x * 2.0f) * i) - ((8 - 1) * (newenemyAttack->transform.scale_.x)) ,
			-newenemyAttack->transform.scale_.y,
			150 };

		/*if (i == a) {
			newenemyAttack->transform.scale_.y = 5.0f;
		}*/

		//格納
		enemyAttack.push_back(newenemyAttack);
	}
}

void Enemy::Avoidance() {

}