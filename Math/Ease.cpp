#include "Ease.h"
#include <math.h>

using::Math::Ease;
using::Math::Ease2;
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


void Ease::Initialize(const Status& state)
{
	ratio_ = 0.0f;

	start_ = state.start_;
	end_ = state.end_;
	power_ = state.power_;

	increase_ = state.increase_;
}

void Ease::Update(const bool isEase)
{
	if (!isEase) { return; }
	
	ratio_ += increase_;
	if (ratio_ >= 1.0f) ratio_ = 1.0f;
}

float Ease::In() { return EaseIn(start_, end_, ratio_, power_); }

float Ease::Out() { return EaseOut(start_, end_, ratio_, power_); }

void Ease2::Initialize(const Status2& state)
{
	ratio_ = 0.0f;

	start_ = state.start_;
	end_ = state.end_;
	power_ = state.power_;

	increase_ = state.increase_;
	decrease_ = state.decrease_;
}

void Ease2::Update(const bool isEase)
{
	if (isEase)
	{
		ratio_ += increase_;
		if (ratio_ >= 1.0f) ratio_ = 1.0f;
	}
	else
	{
		ratio_ -= decrease_;
		if (ratio_ <= 0.0f) ratio_ = 0.0f;
	}
}