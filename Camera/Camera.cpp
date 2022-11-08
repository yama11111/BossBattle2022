#include "Camera.h"
#include "Calc.h"

void Camera::Initialize(Object::Transform::Status state)
{
	shake_.Initialize();
	SetStatus(state);
}

void Camera::SetStatus(Object::Transform::Status state)
{
	pos_ = state.pos_;
	rota_ = state.rota_;
	trfm_.Initialize(state);
	vp_.Initialize({});
	Update();
}

void Camera::Shaking(const float swing, const float dekey)
{
	shake_.Shaking(swing, dekey);
}

void Camera::Update()
{
	trfm_.pos_ = pos_;
	trfm_.rota_ = rota_;

	trfm_.Update();
	shake_.Update();

	// 視点
	vp_.eye_ = trfm_.pos_;
	// 注視点
	Math::Vec3 forward = Math::MultVec3Mat4(Math::Vec3(0, 0, 1), trfm_.m_);
	vp_.target_ = vp_.eye_;
	vp_.target_ += forward;
	// 上方向ベクトル
	vp_.up_ = Math::MultVec3Mat4(Math::Vec3(0, 1, 0), trfm_.m_);

	vp_.Update();
}

Object::ViewProjection Camera::GetViewProjection()
{
	Object::ViewProjection result = vp_;
	result.eye_ += shake_.GetValue();
	result.target_ += shake_.GetValue();
	result.Update();

	return result;
}
