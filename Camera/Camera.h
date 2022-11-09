#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Shake.h"

class Camera
{
public:
	// �ʒu
	Math::Vec3 pos_;
	// ��]
	Math::Vec3 rota_;
private:
	// �g�����X�t�H�[��
	Object::Transform trfm_;
	// �r���[�v���W�F�N�V����
	Object::ViewProjection vp_;
	// �J�����V�F�C�N
	Math::Shake shake_;
public:
	// ������
	void Initialize(Object::Transform::Status state);
	// ������(�J�����V�F�C�N�ȊO)
	void SetStatus(Object::Transform::Status state);
	// �J�����V�F�C�N
	void Shaking(const float swing, const float dekey);
	// trfm �� vp
	void Update();
public:
	// �r���[�v���W�F�N�V����
	Object::ViewProjection GetViewProjection();
	// �h��Ă��邩
	bool IsShake() { return shake_.IsShake(); }
};

