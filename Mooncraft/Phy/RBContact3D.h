#pragma once

#include "math/Vector3.h"

namespace phynet{
namespace phy{

class RigidBody3D;

class RBContact3D
{
public:
	RBContact3D(RigidBody3D* i_first, RigidBody3D* i_second, 
		const math::Vector3& i_contactNormal, 
		const math::Vector3& i_contactPoint, 
		const Real i_penetration, 
		const Real i_restitution,
		const Real i_friction)
	{
		m_rb[0] = i_first;
		m_rb[1] = i_second;
		m_contactNormal = i_contactNormal;
		m_contactPoint = i_contactPoint;
		m_penetration = i_penetration;
		m_restitution = i_restitution;
		m_friction = i_friction;
	}

	void Resolve(const Real i_duration)
	{
		//TODO
	}

	RigidBody3D* m_rb[2];
	math::Vector3 m_contactNormal;
	math::Vector3 m_contactPoint;
	Real m_penetration;
	Real m_restitution;
	Real m_friction;
};

}} // namespace phynet


