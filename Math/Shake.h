#pragma once
#include "Vec3.h"

namespace Math
{
	class Shake
	{
	private:
		// �h��Ă����
		Vec3 value_{};
		// �h��Ă��邩
		bool isShake_ = false;
		// �h���� (����)
		float swingValue_ = 0;
		// ������
		float dekey_ = 0;
	public:
		void Initialize();
		void Update();
		void Shaking(const float swing, const float dekey);
		Vec3 GetValue() { return value_; }
		bool IsShake() { return isShake_; }
		float Ratio() { return 1.0f - dekey_ / swingValue_; }
	};
}