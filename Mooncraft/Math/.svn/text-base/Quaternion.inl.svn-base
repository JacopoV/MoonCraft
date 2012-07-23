namespace phynet{
namespace math{

inline Quaternion& Quaternion::operator*=(const Quaternion& v)
{
	Real a,b,c,d;
	a =	m_data[0]*v.m_data[0]
		- m_data[1]*v.m_data[1]
		- m_data[2]*v.m_data[2]
		- m_data[3]*v.m_data[3];

	b =	m_data[0]*v.m_data[1]
		+ m_data[1]*v.m_data[0]
		+ m_data[2]*v.m_data[3]
		- m_data[3]*v.m_data[2];

	c =	m_data[0]*v.m_data[2]
		+ m_data[2]*v.m_data[0]
		+ m_data[3]*v.m_data[1]
		- m_data[1]*v.m_data[3];

	d =	m_data[0]*v.m_data[3]
		+ m_data[3]*v.m_data[0]
		+ m_data[1]*v.m_data[2]
		- m_data[2]*v.m_data[1];

	Set(a,b,c,d);
	return *this;
}

inline Quaternion operator*(const Quaternion& v, const Quaternion& w)
{
	Quaternion temp(v);
	return temp*=w;
}

inline Quaternion operator*(const Quaternion& v, const Real c)
{
	Quaternion temp(v);
	return temp*=c;
}

inline Quaternion operator*(const Real c, const Quaternion& v)
{
	Quaternion temp(v);
	return temp*=c;
}

inline Quaternion operator/(const Real c, const Quaternion& v)
{
	Quaternion temp(v);
	return temp/=c;
}

inline Quaternion operator+(const Quaternion& v1, const Quaternion& v2)
{
	Quaternion temp(v1);
	return temp+=v2;
}

inline Quaternion operator-(const Quaternion& v1, const Quaternion& v2)
{
	Quaternion temp(v1);
	return temp-=v2;
}

inline Quaternion operator-(const Quaternion& v)
{
	return Quaternion(-v.X(), -v.Y(), -v.Z(), -v.W());
}

inline Quaternion::Quaternion()
{
	Set(0.f, 0.f, 0.f, 0.f);
}

inline Quaternion::Quaternion(const Real i_x, const Real i_y, const Real i_z, const Real i_w)
{
	Set(i_x, i_y, i_z, i_w);
}

inline const Real& Quaternion::X() const
{
	return m_data[0];
}

inline const Real& Quaternion::Y() const
{
	return m_data[1];
}

inline const Real& Quaternion::Z() const
{
	return m_data[2];
}

inline const Real& Quaternion::W() const
{
	return m_data[3];
}

inline Real& Quaternion::X()
{
	return m_data[0];
}

inline Real& Quaternion::Y()
{
	return m_data[1];
}

inline Real& Quaternion::Z()
{
	return m_data[2];
}

inline Real& Quaternion::W()
{
	return m_data[3];
}

inline Real Quaternion::GetElem(int i_index) const
{
	return m_data[i_index];
}

inline void Quaternion::SetElem(int i_index, Real i_val)
{
	m_data[i_index] = i_val;
}

inline void Quaternion::Set(const Real i_x, const Real i_y, const Real i_z, const Real i_w)
{
	m_data[0] = i_x;
	m_data[1] = i_y;
	m_data[2] = i_z;
	m_data[3] = i_w;
}

inline Real Quaternion::SquareMagnitude() const
{
	return X()*X() + Y()*Y() + Z()*Z() + W()*W();
}

inline Quaternion& Quaternion::operator*=(const Real c)
{
	X() *= c;
	Y() *= c;
	Z() *= c;
	W() *= c;
	return *this;
}

inline Quaternion& Quaternion::operator/=(const Real c)
{
	X() /= c;
	Y() /= c;
	Z() /= c;
	W() /= c;
	return *this;
}

inline Quaternion& Quaternion::operator+=(const Quaternion& v)
{
	X() += v.X();
	Y() += v.Y();
	Z() += v.Z();
	W() += v.W();
	return *this;
}

inline Quaternion& Quaternion::operator-=(const Quaternion& v)
{
	X() -= v.X();
	Y() -= v.Y();
	Z() -= v.Z();
	W() -= v.W();
	return *this;
}

inline Quaternion& Quaternion::Normalize()
{
	if(!IsZero())
		*this *= 1.0f / Magnitude();
	return *this;
}

inline Quaternion Quaternion::GetNormalized() const
{
	Quaternion temp(*this);
	return temp.Normalize();
}

inline const Quaternion& Quaternion::ZERO()
{
	static const Quaternion QZero;
	return QZero;
}

}} // namespaces
