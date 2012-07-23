namespace phynet{
namespace math{

inline Polygon2::Polygon2()
{
}

inline Polygon2::Polygon2(const Points& i_points)
	:m_points(i_points)
{
}

inline Polygon2::Polygon2(const Vector2* const i_points, const UInt i_size)
{
	m_points.insert(m_points.begin(), i_points, i_points + i_size);
}

inline 	const Polygon2::Points& Polygon2::GetPoints() const
{
	return m_points;
}

inline void Polygon2::SetPoints(const Points& i_points)
{
	m_points = i_points;
}

}} // namespaces
