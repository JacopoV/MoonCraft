#include "Polygon2.h"

namespace phynet{
namespace math{

bool Polygon2::IsInside(const Vector2& i_point) const
{
	const Real x0 = i_point.X();
	const Real y0 = i_point.Y();

	int numIntersection = 0;
	const size_t numIter = m_points.size();
	for(size_t i=0; i<numIter; ++i)
	{
		size_t j = (i+1)%numIter;

		const Real x1 = m_points[i].X();
		const Real y1 = m_points[i].Y();
		const Real x2 = m_points[j].X();
		const Real y2 = m_points[j].Y();

		const bool a = (y0 < y1);
		const bool b = (y0 < y2);
		if((a && !b) || (!a && b))
		{
			const bool c = (x0 < x1);
			const bool d = (x0 < x2);
			if(c && d)
			{
				++numIntersection;
				continue;
			}
			if(!c && !d)
			{
				continue;
			}

			if((x1 + (x2-x1) * (y0-y1)/(y2-y1)) > x0)
			{
				++numIntersection;
				continue;
			}
		}
	}
	
	return numIntersection%2 == 1;
}

}} // namespaces

