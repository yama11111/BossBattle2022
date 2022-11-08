#include "Player.h"

void Player::Initialize(Model* model) {

	this->model = model;

	Vec4 color = { 1.0f,1.0f,1.0f,1.0f };

	transform.Initialize({ });

}

void Player::Update() {

	transform.Update();
}

void Player::Draw(ViewProjection& vp, const UINT tex) {
	model->Draw(transform, vp, tex);
}