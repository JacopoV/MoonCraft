#pragma once

#include "Vector3.h"

namespace phynet{
namespace math{

struct Plane
{
	Vector3 m_normal;
	Real m_distance;
};

}} // namespaces

#include "Polygon2.inl"
