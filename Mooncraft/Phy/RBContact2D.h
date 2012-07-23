#pragma once

#include "..\Common\Types.h"
#include "..\Math\Vector2.h"

namespace phynet{
namespace phy{

class RBContact2D
{
public:
	RBContact2D(RigidBody2D* i_first, RigidBody2D* i_second, 
		const Vector2& i_contactNormal, 
		const Vector2& i_contactPoint, 
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

private:
	RigidBody2D* m_rb[2];
	Vector2 m_contactNormal;
	Vector2 m_contactPoint;
	Real m_penetration;
	Real m_restitution;
	Real m_friction;
};

}} // namespace phynet


