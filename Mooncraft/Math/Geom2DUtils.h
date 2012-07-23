#pragma once

#include "Vector2.h"
#include "MathUtils.h"

namespace phynet{
namespace math{

// Return minimum distance between line segment AB and point P
inline Real DistancePointSegment(const Vector2& A, const Vector2& B, const Vector2& P)
{
	Vector2 AB = B; AB -= A;
	Vector2 AP = P; AP -= A;
	const Real l2 = AB.SquareMagnitude(); // i.e. |A-B|^2 - avoid a sqrt
	if (AreEqual(l2, 0.0f))
		return AP.Magnitude(); // A == B case

	// Consider the line extending the segment, parameterized as A + t (B - A).
	// We find projection of point P onto the line. 
	// It falls where t = [(P-A) dot (B-A)] / |A-B|^2
	const Real t = Dot(AP, AB) / l2;
	if (LessThan(t, 0.0f))
		return AP.Magnitude();       // Beyond the 'A' end of the segment
	else if (GreaterThan(t, 1.0f))
		return (P - B).Magnitude();  // Beyond the 'B' end of the segment
	const Vector2 projection = A + t * AB;  // Projection falls on the segment
	return (P - projection).Magnitude();
}

}} // namespaces
