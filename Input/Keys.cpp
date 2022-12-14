#include "Keys.h"
#include "YAssert.h"

using Input::Keys;

Keys* Keys::GetInstance()
{
	static Keys instance;
	return &instance;
}

void Keys::Create(const HWND hwnd, IDirectInput8* directInput)
{
	// 生成
	for (size_t i = 0; i < 256; i++)
	{
		keys_[i] = std::make_unique<unsigned char>();
		elderKeys_[i] = std::make_unique<unsigned char>();
	}

	// キーボードデバイス 生成
	DX::Result(directInput->CreateDevice(GUID_SysKeyboard, &device_, NULL));

	// 入力データ形式セット
	DX::Result(device_->SetDataFormat(&c_dfDIKeyboard));

	// 排他制御レベルセット
	DX::Result(device_->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));

	Initialize();
}

void Keys::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		*keys_[i] = *elderKeys_[i] = 0;
	}
}

void Keys::Update()
{
	// 1フレーム前の情報を保存
	for (int i = 0; i < 256; i++) { *elderKeys_[i] = *keys_[i]; }

	// 最新の情報を取得
	device_->Acquire();

	// 入力状態を取得
	BYTE key[256];
	device_->GetDeviceState(sizeof(key), key);

	for (int i = 0; i < 256; i++) { *keys_[i] = key[i]; }
}

bool Keys::IsDown(const int key)
{
	return *keys_[key];
}
bool Keys::IsTrigger(const int key)
{
	return (*keys_[key] && !*elderKeys_[key]);
}
bool Keys::IsLongPress(const int key)
{
	return (*keys_[key] && *elderKeys_[key]);
}
bool Keys::IsRelease(const int key)
{
	return (!*keys_[key] && *elderKeys_[key]);
}

bool Keys::IsLeft()
{
	return IsDown(DIK_LEFT) || IsDown(DIK_A);
}
bool Keys::IsRight()
{
	return IsDown(DIK_RIGHT) || IsDown(DIK_D);
}
bool Keys::IsUp()
{
	return IsDown(DIK_UP) || IsDown(DIK_W);
}
bool Keys::IsUnder()
{
	return IsDown(DIK_DOWN) || IsDown(DIK_S);
}

int Keys::Horizontal()
{
	return IsRight() - IsLeft();
}
int Keys::Vertical()
{
	return IsUnder() - IsUp();
}
bool Keys::IsMove()
{
	return IsRight() || IsLeft() || IsUp() || IsUnder();
}