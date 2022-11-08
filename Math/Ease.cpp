#include "Ease.h"
#include <math.h>
#include "Vec2.h"

using::Math::Ease;
//using::Math::Ease2;
using::Math::Vec2;
using::Math::Vec3;

float Math::Lerp(const float a, const float b, const float t)
{
	return a + t * (b - a);
}
Vec3 Math::Lerp(const Vec3& v1, const Vec3& v2, float t)
{
	//Vec3 result = ((v2 - v1) * t) + v1;
	//return result;
	return Vec3();
}
Vec3 Math::Slerp(const Vec3& v1, const Vec3& v2, float t)
{
	//float dot = v1.Dot(v2);
	//if (dot >= 1.0 || dot <= -1.0) return v1;

	//float theta = acosf(dot);
	//float sTheta = sinf(theta);
	//float sf = sinf((1 - t) * theta);
	//float st = sinf(t * theta);

	//float aS = v1.Length();
	//float bS = v2.Length();
	//float s = aS + t * (bS - aS);

	//Vec3 from = v1 * sf;
	//Vec3 to = v2 * st / sTheta;
	//Vec3 result = (from + to) * s;
	//return result;

	return Vec3();
}

float Math::EaseIn(const float start, const float end, const float time, const float power)
{
	return Lerp(start, end, powf(time, power));
}
float Math::EaseOut(const float start, const float end, const float time, const float power)
{
	return Lerp(start, end, 1 - powf(1 - time, power));
}

template<typename T>
void Ease<T>::Initialize(const T& start, const T& end, const float power, const float increase)
{
	ratio_ = 0.0f;

	start_ = start;
	end_ = end;
	power_ = power;

	increase_ = increase;
}

template<typename T>
void Ease<T>::Update(const bool isEase)
{
	if (!isEase) { return; }
	
	ratio_ += increase_;
	if (ratio_ >= 1.0f) ratio_ = 1.0f;
}

template<typename T>
T Ease<T>::In() { return EaseIn(start_, end_, ratio_, power_); }

template<>
Vec2 Ease<Vec2>::In()
{
	return Vec2
	(
		EaseIn(start_.x, end_.x, ratio_, power_), 
		EaseIn(start_.y, end_.y, ratio_, power_)
	);
}

template<>
Vec3 Ease<Vec3>::In()
{
	return Vec3
	(
		EaseIn(start_.x, end_.x, ratio_, power_),
		EaseIn(start_.y, end_.y, ratio_, power_),
		EaseIn(start_.z, end_.z, ratio_, power_)
	);
}

template<typename T>
T Ease<T>::Out() { return EaseOut(start_, end_, ratio_, power_); }

template<>
Vec2 Ease<Vec2>::Out()
{
	return Vec2
	(
		EaseOut(start_.x, end_.x, ratio_, power_),
		EaseOut(start_.y, end_.y, ratio_, power_)
	);
}

template<>
Vec3 Ease<Vec3>::Out()
{
	return Vec3
	(
		EaseOut(start_.x, end_.x, ratio_, power_),
		EaseOut(start_.y, end_.y, ratio_, power_),
		EaseOut(start_.z, end_.z, ratio_, power_)
	);
}

//template<typename T>
//void Ease2<T>::Initialize(const T& start, const T& end, const float power, const float increase, const float decrease)
//{
//	ratio_ = 0.0f;
//
//	start_ = start;
//	end_ = end;
//	power_ = power;
//
//	increase_ = increase;
//	decrease_ = decrease;
//}
//
//template<typename T>
//void Ease2<T>::Update(const bool isEase)
//{
//	if (isEase)
//	{
//		ratio_ += increase_;
//		if (ratio_ >= 1.0f) ratio_ = 1.0f;
//	}
//	else
//	{
//		ratio_ -= decrease_;
//		if (ratio_ <= 0.0f) ratio_ = 0.0f;
//	}
//}

template class Ease<int>;
template class Ease<float>;
template class Ease<double>;
template class Ease<Vec2>;
template class Ease<Vec3>;

//template class Ease2<int>;
//template class Ease2<float>;
//template class Ease2<double>;
//template class Ease2<Vec2>;
//template class Ease2<Vec3>;