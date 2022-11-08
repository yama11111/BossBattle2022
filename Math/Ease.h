#pragma once
#include "Vec3.h"

namespace Math
{
	float Lerp(const float a, const float b, const float t);
	Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t);
	Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);
	float EaseIn(const float start, const float end, const float time, const float power);
	float EaseOut(const float start, const float end, const float time, const float power);

	class Ease
	{
	protected:
		float ratio_ = 0.0f;
		float start_ = 0.0f;
		float end_ = 0.0f;
		float power_ = 0.0f;
		float increase_ = 0.0f;
	public:
		struct Status
		{
			float start_ = 0.0f;
			float end_ = 0.0f;
			float power_ = 0.0f;
			float increase_ = 0.0f;
		};
	public:
		void Initialize(const Status& state);
		virtual void Update(const bool isEase);
		float In();
		float Out();
	};

	class Ease2 : public Ease
	{
	private:
		float decrease_ = 0.0f;
	public:
		struct Status2 : public Status
		{
			float decrease_ = 0.0f;
		};
	public:
		void Initialize(const Status2& state);
		void Update(const bool isEase) override;
	};
}