#pragma once
#include "Vec3.h"

namespace Math
{
	class Shake
	{
	private:
		// —h‚ê‚Ä‚¢‚é—Ê
		Vec3 value_{};
		// —h‚ê‚Ä‚¢‚é‚©
		bool isShake_ = false;
		// —h‚ê‚é—Ê (—”)
		float swingValue_ = 0;
		// Œ¸Š—Ê
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