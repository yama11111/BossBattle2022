#pragma once
#include "Vec3.h"

namespace Math
{
	template<typename T>
	T Lerp(const T& a, const T& b, const float t);
	Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);
	template<typename T>
	T EaseIn(const T& start, const T& end, const float time, const float power);
	template<typename T>
	T EaseOut(const T& start, const T& end, const float time, const float power);

	template<typename T>
	class Ease
	{
	private:
		T start_;
		T end_;
		float power_ = 0.0f;
	public:
		void Initialize(const T& start, const T& end, const float power);
		T In(const float time);
		T Out(const float time);
	public:
		void SetStart(const T& start) { start_ = start; };
		void SetEnd(const T& end) { end_ = end; };
		void SetPower(const float power) { power_ = power; }
	};
}