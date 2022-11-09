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

	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	key = Keys::GetInstance();

	transform.Initialize({ });
}

void Player::Update() {

	//スピード
	const float speed = 0.3f;

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

	//移動限界
	const float kMoveLimitX = 48;
	const float kMoveLimitZ = 48;
	const float kMoveLimitY = 14;

	////範囲を超えない処理
	transform.pos_.y = max(transform.pos_.y, -kMoveLimitY);
	transform.pos_.y = min(transform.pos_.y, +kMoveLimitY);
	transform.pos_.x = max(transform.pos_.x, -kMoveLimitX);
	transform.pos_.x = min(transform.pos_.x, +kMoveLimitX);
	transform.pos_.z = max(transform.pos_.z, -kMoveLimitZ);
	transform.pos_.z = min(transform.pos_.z, +kMoveLimitZ);

	key->Update();
	transform.Update();
}

void Player::Draw(ViewProjection& vp, const UINT tex) {
	model->Draw(transform, vp, tex);
}