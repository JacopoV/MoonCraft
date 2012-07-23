namespace phynet{
namespace math{

inline Real Distance(const Vector2& v1, const Vector2& v2)
{
	return (v1-v2).Magnitude();
}

inline Real Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.X()*v2.X() + v1.Y()*v2.Y();
}

inline Vector2 operator*(const Vector2& v, const Real c)
{
	Vector2 temp(v);
	return temp*=c;
}

inline Vector2 operator*(const Real c, const Vector2& v)
{
	Vector2 temp(v);
	return temp*=c;
}

inline Vector2 operator/(const Vector2& v, const Real c)
{
	Vector2 temp(v);
	return temp/=c;
}

inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp+=v2;
}

inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	return temp-=v2;
}

inline Vector2 operator-(const Vector2& v)
{
	return Vector2(-v.X(), -v.Y());
}

inline Vector2::Vector2()
{
	m_data[0] = 0.f;
	m_data[1] = 0.f;
}

inline Vector2::Vector2(const Real i_x, const Real i_y)
{
	m_data[0] = i_x;
	m_data[1] = i_y;
}

inline const Real& Vector2::X() const
{
	return m_data[0];
}

inline const Real& Vector2::Y() const
{
	return m_data[1];
}

inline Real& Vector2::X()
{
	return m_data[0];
}

inline Real& Vector2::Y()
{
	return m_data[1];
}

inline Real Vector2::GetElem(int i_index) const
{
	return m_data[i_index];
}

inline void Vector2::SetElem(int i_index, Real i_val)
{
	m_data[i_index] = i_val;
}

inline void Vector2::Set(const Real i_x, const Real i_y)
{
	m_data[0] = i_x;
	m_data[1] = i_y;
}

inline Real Vector2::Magnitude() const
{
	return sqrt(SquareMagnitude());
}

inline Real Vector2::SquareMagnitude() const
{
	return X()*X() + Y()*Y();
}

inline Vector2& Vector2::operator*=(const Real c)
{
	X() *= c;
	Y() *= c;
	return *this;
}

inline Vector2& Vector2::operator/=(const Real c)
{
	X() /= c;
	Y() /= c;
	return *this;
}

inline Vector2& Vector2::operator+=(const Vector2& v)
{
	X() += v.X();
	Y() += v.Y();
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& v)
{
	X() -= v.X();
	Y() -= v.Y();
	return *this;
}

inline Vector2& Vector2::Normalize()
{
	if(!IsZero())
		*this *= 1.0f / Magnitude();
	return *this;
}

inline Vector2 Vector2::GetNormalized() const
{
	Vector2 temp(*this);
	return temp.Normalize();
}

inline bool Vector2::IsZero() const
{
	return AreEqual(X(), 0.0f) && AreEqual(Y(), 0.0f);
}

inline const Vector2& Vector2::ZERO()
{
	return vector2::ZERO;
}

}} // namespaces
