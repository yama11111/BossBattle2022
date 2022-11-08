#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Shake.h"

class Camera
{
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
	// �J�����V�F�C�N
	void Shaking(const float swing, const float dekey);
	// trfm �� vp
	void Update();
public:
	// �r���[�v���W�F�N�V����
	Object::ViewProjection GetViewProjection();
	// �ʒu�ݒ�
	void SetPos(const Math::Vec3& pos) { trfm_.pos_ = pos; };
	// ��]�ݒ�
	void SetRota(const Math::Vec3& rota) { trfm_.rota_ = rota; };
};

