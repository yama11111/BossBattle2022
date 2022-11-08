#include "Camera.h"
#include "Calc.h"

void Camera::Initialize(Object::Transform::Status state)
{
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
	trfm_.Update();
	shake_.Update();

	// ���_
	vp_.eye_ = trfm_.pos_;
	// �����_
	Math::Vec3 forward = Math::MultVec3Mat4(Math::Vec3(0, 0, 1), trfm_.m_);
	vp_.target_ = vp_.eye_;
	vp_.target_ += forward;
	// ������x�N�g��
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
