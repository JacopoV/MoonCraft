#pragma once

#include <vector>
#include "Vector2.h"

namespace phynet{
namespace math{

class Polygon2
{
public:
	typedef std::vector<Vector2> Points;
	
	Polygon2();
	explicit Polygon2(const Points& i_points);
	Polygon2(const Vector2* const i_points, const UInt i_size); 

	const Points& GetPoints() const;
	void SetPoints(const Points& i_points);

	bool IsInside(const Vector2& i_point) const;

private:
	Points m_points;
};

}} // namespaces

#include "Polygon2.inl"
