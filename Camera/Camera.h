#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Shake.h"

class Camera
{
private:
	// トランスフォーム
	Object::Transform trfm_;
	// ビュープロジェクション
	Object::ViewProjection vp_;
	// カメラシェイク
	Math::Shake shake_;
public:
	// 初期化
	void Initialize(Object::Transform::Status state);
	// カメラシェイク
	void Shaking(const float swing, const float dekey);
	// trfm → vp
	void Update();
public:
	// ビュープロジェクション
	Object::ViewProjection GetViewProjection();
	// 位置設定
	void SetPos(const Math::Vec3& pos) { trfm_.pos_ = pos; };
	// 回転設定
	void SetRota(const Math::Vec3& rota) { trfm_.rota_ = rota; };
};

