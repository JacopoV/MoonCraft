#pragma once

#include "Vector3.h"
#include "Matrix.h"

namespace phynet{

namespace phy{
	class RigidBody3D;
}

namespace math{

struct Primitive3D
{
	phy::RigidBody3D* m_rb;
};

struct Plane : Primitive3D
{
	Vector3 m_normal;
	Real m_distance;
};

struct Line3D : Primitive3D
{
	Vector3 m_point;
	Vector3 m_direction;
};

struct Sphere : Primitive3D
{
	Vector3 m_center;
	Real m_radious;
};

struct Box3D : Primitive3D
{
	Vector3 m_dimensions;
	Matrix34 m_transform;
};


}} // namespaces
