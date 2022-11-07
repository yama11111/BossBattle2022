#include "Player.h"

void Player::Initialize(TextureManager* textre) {

	//transform.Initialize();

	t = textre;
	model.StaticInitialize(t);
}

void Player::Update() {


	transform.Update();
}

void Player::Draw(Math::MatViewProjection& vp, const UINT tex) {
	model.Draw(transform, vp, tex);
}