#include "Player.h"

Vec3 Player::GetWorldPosition() {
	Vec3 worldPos;

	worldPos.x = transform.pos_.x;
	worldPos.y = transform.pos_.y;
	worldPos.z = transform.pos_.z;

	return worldPos;
}

void Player::Initialize(Model* model) {

	this->model = model;

	Attackmodel = model;

	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	key = Keys::GetInstance();

	transform.Initialize({ });
	transform.scale_ = { 5.0f,5.0f,5.0f };

	attack.Initialize({ });
	attack.scale_ = { 10.0f,10.0f,10.0f };

	jumpCount = 0;

	AttackF = false;
}

void Player::Update() {

	//スピード
	const float speed =	2.0f;

	if (key->IsDown(DIK_W)) {
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
	};

	//ジャンプ
	Jump();
	Attack();

	////範囲を超えない処理
	transform.pos_.y = min(transform.pos_.y, kMoveLimitY * 3);
	transform.pos_.y = max(transform.pos_.y, transform.scale_.y);
	transform.pos_.x = max(transform.pos_.x, -kMoveLimitX);
	transform.pos_.x = min(transform.pos_.x, +kMoveLimitX);
	transform.pos_.z = max(transform.pos_.z, -kMoveLimitZ);
	transform.pos_.z = min(transform.pos_.z, +kMoveLimitZ);

	transform.Update();
	attack.Update();
}

void Player::Draw(ViewProjection& vp, const UINT tex, const UINT tex2) {
	model->Draw(transform, vp, tex);

	if (AttackF == true) {
		model->Draw(attack, vp, tex2);
	}
}

void Player::Jump() {
	if (key->IsTrigger(DIK_Z)) {

		if (transform.pos_.y < kMoveLimitY + 1) {

			Gravity = 0;

			jump = Maxjump;

			jumpCount = 0;
		}
	}

	//ジャンプ
	if (Gravity < MaxGravity) {
		Gravity += 0.02f;
	}

	if (jump > 0) {
		transform.pos_.y += jump;

		jumpCount++;

		jump -= 0.1f * jumpCount;
	}
	else {
		transform.pos_.y -= Gravity;
	}
}

void Player::Attack() {
	if (key->IsTrigger(DIK_SPACE)) {
		if (AttackF != true) {

			AttackF = true;
		}
	}

	if (AttackF == true) {
		attack.pos_ = transform.pos_;
		attack.pos_.x += 20;
	}

	if (key->IsTrigger(DIK_R)) {
		AttackF = false;
	}
}

void Player::Avoidance() {

}