#pragma once

#include "Common/Types.h"
#include "math/Matrix.h"
#include "math/Circle2.h"
#include "math/Primitives2D.h"
#include "math/Primitives3D.h"
#include "RBContact3D.h"
#include "RigidBody3d.h"

namespace phynet{
namespace phy{

inline void applyTransform(const math::Matrix23& i_matrix, math::Vector2& io_vector)
{
	//todo
}

inline const math::Vector2 transform(const math::Matrix23& i_matrix, const math::Vector2& i_vector)
{
	math::Vector2 temp(i_vector);
	applyTransform(i_matrix, temp);
	return temp;
}

inline const math::Circle2& INVALID_BS()
{
	const static math::Circle2 s_invalid_bs(math::Vector2::ZERO(), -1.0f);
	return s_invalid_bs;
}

inline bool IsInvalidBS(const math::Circle2& i_bs)
{
	return math::AreEqual(-1.0f, i_bs.GetRadius());
}

inline math::Vector2 SpinorProduct(const math::Vector2& i_first, const math::Vector2& i_second)
{
	return math::Vector2
		(i_first.X() * i_second.X() - i_first.Y() * i_second.Y(),
		i_first.X() * i_second.Y() + i_first.Y() * i_second.X());
}

class RigidBody2D;
class RigidBody3D;

template<int Dim> struct RigidBodyType{};
template<> struct RigidBodyType<2>
{
	typedef math::Vector2 VectorType;
	typedef RigidBody2D Type;
};

template<> struct RigidBodyType<3>
{
	typedef math::Vector3 VectorType;
	typedef RigidBody3D Type;
};

inline bool SphereSphereCollisionTest(const math::Sphere& i_first, const math::Sphere& i_second, RBContact3D& o_contact)
{
	//TODO
	return false;
}

inline bool SpherePlaneCollisionTest(const math::Sphere& i_first, const math::Plane& i_second, RBContact3D& o_contact)
{
	const Real l = Dot(i_first.m_center, i_second.m_normal);
	const Real dist = l - i_second.m_distance;

	if(fabs(l - dist) < i_first.m_radious)
	{
		//TODO
		return true;
	}

	return false;
}

inline bool SphereHalfSpaceCollisionTest(const math::Sphere& i_first, const math::Plane& i_second, RBContact3D& o_contact)
{
	const Real l = Dot(i_first.m_center, i_second.m_normal);
	const Real dist = l - i_second.m_distance;

	const Real penetration = (l - dist) - i_first.m_radious; 
	if(penetration > 0)
	{
		o_contact.m_rb[0] = i_first.m_rb;
		o_contact.m_rb[1] = i_second.m_rb;
		o_contact.m_contactNormal = i_second.m_normal;
		o_contact.m_contactPoint = i_first.m_center - i_second.m_normal*i_first.m_radious;
		o_contact.m_penetration = penetration;
		o_contact.m_restitution = i_first.m_rb->GetElasticity() * i_second.m_rb->GetElasticity();
		o_contact.m_friction = 0.0f; // TODO
		return true;
	}

	return false;
}

}} // namespaces

