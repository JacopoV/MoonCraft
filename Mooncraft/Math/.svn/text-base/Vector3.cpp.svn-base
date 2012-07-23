#include "math/Vector3.h"
#include "math/MathUtils.h"

#include <cmath>

namespace phynet{
namespace math{

namespace vector3
{
const Vector3 ZERO(0.f, 0.f, 0.f);
const Vector3 X_VERSOR(1.f, 0.f, 0.f);
const Vector3 Y_VERSOR(0.f, 1.f, 0.f);
const Vector3 Z_VERSOR(0.f, 0.f, 1.f);
}

Real Vector3::Magnitude() const
{
	return sqrt(SquareMagnitude());
}

bool Vector3::IsZero() const
{
	return AreEqual(X(), 0.0f) && AreEqual(Y(), 0.0f) && AreEqual(Z(), 0.0f);
}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(	v1.Y()*v2.Z() - v1.Z()*v2.Y(),
					v1.Z()*v2.X() - v1.X()*v2.Z(),
					v1.X()*v2.Y() - v1.Y()*v2.X());
}

}} // namespaces
