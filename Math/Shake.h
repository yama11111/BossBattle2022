#pragma once
#include "Vec3.h"

namespace Math
{
	class Shake
	{
	private:
		// 揺れている量
		Vec3 value_{};
		// 揺れているか
		bool isShake_ = false;
		// 揺れる量 (乱数)
		float swingValue_ = 0;
		// 減衰量
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