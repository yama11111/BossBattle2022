#pragma once

namespace Math
{
	struct Vec3
	{
	public:
		float x;
		float y;
		float z;
	public:
		Vec3(); // 零ベクトル
		Vec3(float x, float y, float z);

		float Length() const;					// ノルム(長さ)
		constexpr float LengthSquare() const;	// 長さ 2乗
		Vec3 Normalized() const;				// 正規化
		constexpr bool IsZero() const;			// 零ベクトルか

		constexpr float Dot(const Vec3& v) const; // 内積
		Vec3 Cross(const Vec3& v); // 外積
		float Distance(const Vec3& v) const; // 距離
	public:
		// 単項演算子
		Vec3 operator+() const;
		Vec3 operator-() const;

		// 代入演算子
		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);
		Vec3& operator*=(float s);
		Vec3& operator/=(float s);
	};

	// 二項演算子
	inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
	{
		return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}
	inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
	{
		return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}
	inline Vec3 operator*(const Vec3& v, float s)
	{
		return { v.x * s, v.y * s, v.z * s };
	}
	inline Vec3 operator*(float s, const Vec3& v)
	{
		return { s * v.x, s * v.y, s * v.z };
	}
	inline Vec3 operator/(const Vec3& v, float s)
	{
		return { v.x / s, v.y / s, v.z / s };
	}
}