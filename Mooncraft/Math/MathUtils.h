#pragma once

#include "common/Types.h"

namespace phynet{
namespace math{

inline bool AreEqual(const Real x, const Real y, const Real tolerance = 0.001)
{
	const Real diff = x-y;
	return (diff >= -tolerance) && (diff <= tolerance);
}

inline bool GreaterThan(const Real x, const Real y, const Real tolerance = 0.001)
{
	return (x-y > tolerance);
}

inline bool GreaterThanOrEqual(const Real x, const Real y, const Real tolerance = 0.001)
{
	return (x-y >= -tolerance);
}

inline bool LessThan(const Real x, const Real y, const Real tolerance = 0.001)
{
	return (y-x > tolerance);
}

inline bool LessThanOrEqual(const Real x, const Real y, const Real tolerance = 0.001)
{
	return (y-x >= -tolerance);
}

}} // namespaces
