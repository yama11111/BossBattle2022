#pragma once
#include "Vec3.h"

namespace Math
{
	float Lerp(const float a, const float b, const float t);
	Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t);
	Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);
	float EaseIn(const float start, const float end, const float time, const float power);
	float EaseOut(const float start, const float end, const float time, const float power);

	template<typename T>
	class Ease
	{
	protected:
		float ratio_ = 0.0f;
		T start_;
		T end_;
		float power_ = 0.0f;
		float increase_ = 0.0f;
	public:
		void Initialize(const T& start, const T& end, const float power, const float increase);
		void Reset() { ratio_ = 0.0f; }
		virtual void Update(const bool isEase);
		T In();
		T Out();
	};

	//template <typename T>
	//class Ease2 : public Ease<T>
	//{
	//private:
	//	float decrease_ = 0.0f;
	//public:
	//	void Initialize(const T& start, const T& end, const float power, const float increase, const float decrease);
	//	void Update(const bool isEase) override;
	//};
}