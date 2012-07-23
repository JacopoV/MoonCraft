#pragma once

#include "Vector2.h"
#include "Matrix.h"

namespace phynet{
namespace math{

class RigidBody2D;

struct Primitive2D
{
	RigidBody2D* m_rb;
};

struct Line2D : Primitive2D
{
	Vector2 m_point;
	Vector2 m_direction;
};

struct Circle : Primitive2D
{
	Vector2 m_center;
	Real m_radious;
};

struct Box2D : Primitive2D
{
	Vector2 m_dimensions;
	Matrix23 m_transform;
};

}} // namespaces
