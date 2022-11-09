#include "Shake.h"
#include "Random.h"

using Math::Shake;

void Shake::Initialize()
{
	value_ = { 0,0,0 };
	isShake_ = false;
	swingValue_ = 0;
	dekey_ = 0;
}

void Shake::Shaking(const float swing, const float dekey)
{
	if (!isShake_)
	{
		value_ = { 0,0,0 };
		isShake_ = true;
		dekey_ = dekey;
		swingValue_ = swing;
	}
	else if(swingValue_ <= swing)
	{
		dekey_ = dekey;
		swingValue_ = swing;
	}
}

void Shake::Update() 
{
	// ”ÍˆÍ‚ğ‹·‚ß‚é
	if (swingValue_ > 0) { swingValue_ -= dekey_; }

	// ”ÍˆÍ“à‚Ì—”¶¬
	if (isShake_) 
	{
		value_.x = GetRandF(-swingValue_, swingValue_, 4);
		value_.y = GetRandF(-swingValue_, swingValue_, 4);
		value_.z = GetRandF(-swingValue_, swingValue_, 4);
	}

	if (swingValue_ <= 0) 
	{
		value_ = { 0,0,0 };
		swingValue_ = 0;
		dekey_ = 0;
		isShake_ = false;
	}
}
