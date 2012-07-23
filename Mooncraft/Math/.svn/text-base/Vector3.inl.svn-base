namespace phynet{
namespace math{

inline Real Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
}

inline Vector3 operator*(const Vector3& v, const Real c)
{
	Vector3 temp(v);
	return temp*=c;
}

inline Vector3 operator*(const Real c, const Vector3& v)
{
	Vector3 temp(v);
	return temp*=c;
}

inline Vector3 operator/(const Real c, const Vector3& v)
{
	Vector3 temp(v);
	return temp/=c;
}

inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp+=v2;
}

inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp-=v2;
}

inline Vector3 operator-(const Vector3& v)
{
	return Vector3(-v.X(), -v.Y(), -v.Z());
}

inline Vector3::Vector3()
{
	Set(0.f, 0.f, 0.f);
}

inline Vector3::Vector3(const Real i_x, const Real i_y, const Real i_z)
{
	Set(i_x, i_y, i_z);
}

inline const Real& Vector3::X() const
{
	return m_data[0];
}

inline const Real& Vector3::Y() const
{
	return m_data[1];
}

inline const Real& Vector3::Z() const
{
	return m_data[2];
}

inline Real& Vector3::X()
{
	return m_data[0];
}

inline Real& Vector3::Y()
{
	return m_data[1];
}

inline Real& Vector3::Z()
{
	return m_data[2];
}

inline Real Vector3::GetElem(int i_index) const
{
	return m_data[i_index];
}

inline void Vector3::SetElem(int i_index, Real i_val)
{
	m_data[i_index] = i_val;
}

inline void Vector3::Set(const Real i_x, const Real i_y, const Real i_z)
{
	m_data[0] = i_x;
	m_data[1] = i_y;
	m_data[2] = i_z;
}

inline Real Vector3::SquareMagnitude() const
{
	return X()*X() + Y()*Y() + Z()*Z();
}

inline Vector3& Vector3::operator*=(const Real c)
{
	X() *= c;
	Y() *= c;
	Z() *= c;
	return *this;
}

inline Vector3& Vector3::operator/=(const Real c)
{
	X() /= c;
	Y() /= c;
	Z() /= c;
	return *this;
}

inline Vector3& Vector3::operator+=(const Vector3& v)
{
	X() += v.X();
	Y() += v.Y();
	Z() += v.Z();
	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& v)
{
	X() -= v.X();
	Y() -= v.Y();
	Z() -= v.Z();
	return *this;
}

inline Vector3& Vector3::Normalize()
{
	if(!IsZero())
		*this *= 1.0f / Magnitude();
	return *this;
}

inline Vector3 Vector3::GetNormalized() const
{
	Vector3 temp(*this);
	return temp.Normalize();
}

inline const Vector3& Vector3::ZERO()
{
	return vector3::ZERO;
}

}} // namespaces
