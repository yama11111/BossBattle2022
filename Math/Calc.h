#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"
#define PI 3.141592f

namespace Math
{
	// gkÏ·
	Mat4 MatScale(const Vec3& s);

	// X²ñ]Ï·
	Mat4 MatRotationX(float angle);
	// Y²ñ]Ï·
	Mat4 MatRotationY(float angle);
	// Z²ñ]Ï·
	Mat4 MatRotationZ(float angle);
	// ñ]Ï·(Z¨X¨Y)
	Mat4 MatRotation(const Vec3& r);

	// ÀWÏ·
	Mat4 MatTranslation(const Vec3& t);

	Vec3 MatTransform(const Vec3& v, const Mat4& m);
	Vec3 operator*(const Vec3& v, const Mat4& m);

	// Vector3 * Matrix4
	Vec3 MultVec3Mat4(const Vec3& v, const Mat4& m);
	// Vector4 * Matrix4
	Vec4 MultVec4Mat4(const Vec4& v, const Mat4& m);
	// tsñ
	Mat4 InverceMat4(const Mat4& m);

	// ½seÏ·sñ
	Mat4 MatOrthoGraphic();
	// §eÏ·sñ
	Mat4 MatPerspective();
	// r[|[gsñ
	Mat4 MatViewPort();
	// r[sñ(¶èÀWn)
	Mat4 MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up);

	// 2DÀW¨3DÀW
	Vec3 WorldPos(const Vec2& screen, float z, const Mat4& view, const Mat4& projection);

	// px²®
	Vec3 AdjustAngle(Vec3& velocity);

	float Lerp(const float a, const float b, const float t);

	Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t);
	Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);

	// FÏ·((0`255)¨(0.0`1.0))
	Vec4 GetColor(const Vec4& color);

	// A^»è(ü~)
	bool CollRaySphere(
		const Vec3& ray, const Vec3& velocity,
		const Vec3& sphere, const float rad);

	// A^»è(ü~) <ÑÊ_æ¾ver>
	bool CollRaySphere(
		const Vec3& ray, const Vec3& velocity,
		const Vec3& sphere, const float rad,
		Vec3& start, Vec3& end);
}