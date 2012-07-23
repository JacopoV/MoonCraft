#pragma once

#include "common/Types.h"

namespace phynet{
namespace math{

class Quaternion
{
public:
	Quaternion();
	Quaternion(const Real i_x, const Real i_y, const Real i_z, const Real i_w);

	const Real&	X() const;
	const Real&	Y() const;
	const Real&	Z() const;
	const Real&	W() const;
	Real& X();
	Real& Y();
	Real& Z();
	Real& W();

	Real GetElem(int i_index) const;
	void SetElem(int i_index, Real i_val);

	Real Magnitude() const;
	Real SquareMagnitude() const;

	Quaternion& Normalize();
	Quaternion GetNormalized() const;

	Quaternion& operator*=(const Real c);
	Quaternion& operator/=(const Real c);
	Quaternion& operator+=(const Quaternion& v);
	Quaternion& operator-=(const Quaternion& v);
	
	Quaternion& operator*=(const Quaternion& v);

	void Set(const Real i_x, const Real i_y, const Real i_z, const Real i_w);
	void Zero() { Set(0.f, 0.f, 0.f, 0.f); }
	bool IsZero() const;
	static const Quaternion& ZERO();

private:
	Real m_data[4];
};

Quaternion operator*(const Quaternion& v, const Real c);
Quaternion operator*(const Real c, const Quaternion& v);
Quaternion operator*(const Quaternion& v, const Quaternion& w);

Quaternion operator/(const Quaternion& v, const Real c);

Quaternion operator+(const Quaternion& v1, const Quaternion& v2);
Quaternion operator-(const Quaternion& v1, const Quaternion& v2);

Quaternion operator-(const Quaternion& v);

}} // namespaces

#include "Quaternion.inl"
