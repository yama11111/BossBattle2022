#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "Shake.h"

class Camera
{
public:
	// 位置
	Math::Vec3 pos_;
	// 回転
	Math::Vec3 rota_;
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
	// 初期化(カメラシェイク以外)
	void SetStatus(Object::Transform::Status state);
	// カメラシェイク
	void Shaking(const float swing, const float dekey);
	// trfm → vp
	void Update();
public:
	// ビュープロジェクション
	Object::ViewProjection GetViewProjection();
	// 揺れているか
	bool IsShake() { return shake_.IsShake(); }
};

