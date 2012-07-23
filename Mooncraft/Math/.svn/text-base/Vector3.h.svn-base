#pragma once

#include "common/Types.h"

namespace phynet{
namespace math{


class Vector3
{
public:
	Vector3();
	Vector3(const Real i_x, const Real i_y, const Real i_z);

	const Real&	X() const;
	const Real&	Y() const;
	const Real&	Z() const;
	Real& X();
	Real& Y();
	Real& Z();

	Real GetElem(int i_index) const;
	void SetElem(int i_index, Real i_val);

	Real Magnitude() const;
	Real SquareMagnitude() const;

	Vector3& Normalize();
	Vector3 GetNormalized() const;

	Vector3& operator*=(const Real c);
	Vector3& operator/=(const Real c);
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);

	void Set(const Real i_x, const Real i_y, const Real i_z);
	void Zero() { Set(0.f, 0.f, 0.f); }
	bool IsZero() const;
	static const Vector3& ZERO();

private:
	Real m_data[3];
};

namespace vector3
{
	extern const Vector3 ZERO;
	extern const Vector3 X_VERSOR;
	extern const Vector3 Y_VERSOR;
	extern const Vector3 Z_VERSOR;
}

Real Dot(const Vector3& v1, const Vector3& v2);
Vector3 Cross(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v, const Real c);
Vector3 operator*(const Real c, const Vector3& v);
Vector3 operator/(const Vector3& v, const Real c);
Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v);

}} // namespaces

#include "Vector3.inl"
