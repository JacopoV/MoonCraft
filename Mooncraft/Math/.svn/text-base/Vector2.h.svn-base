#pragma once

#include "Common/Types.h"
#include "math/MathUtils.h"

#include <cmath>

namespace phynet{
namespace math{

class Vector2
{
public:
	Vector2();
	Vector2(const Real i_x, const Real i_y);

	const Real&	X() const;
	const Real&	Y() const;
	Real& X();
	Real& Y();

	Real GetElem(int i_index) const;
	void SetElem(int i_index, Real i_val);

	Real Magnitude() const;
	Real SquareMagnitude() const;

	Vector2& Normalize();
	Vector2 GetNormalized() const;

	Vector2& operator*=(const Real c);
	Vector2& operator/=(const Real c);
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);

	void Set(const Real i_x, const Real i_y);
	void Zero() { Set(0.f, 0.f); }
	bool IsZero() const;
	static const Vector2& ZERO();

private:
	Real m_data[2];
};

namespace vector2
{
extern const Vector2 ZERO;
extern const Vector2 X_VERSOR;
extern const Vector2 Y_VERSOR;
}

Real Distance(const Vector2& v1, const Vector2& v2);
Real Dot(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v, const Real c);
Vector2 operator*(const Real c, const Vector2& v);
Vector2 operator/(const Vector2& v, const Real c);
Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v);

}} // namespaces

#include "Vector2.inl"
