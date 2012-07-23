#pragma once
#include "Math\MathTypes.h"

namespace phynet{
namespace phy{

class RigidBody2d;

class RigidBodyContact
{
public:
	RigidBodyContact(void);
	~RigidBodyContact(void);

	RigidBodyContact(RigidBody2d* i_first, RigidBody2d* i_second, const phynet::math::Vector2& i_contactNormal, const Real i_penetration, const Real i_restitution);
	void Init(RigidBody2d* i_first, RigidBody2d* i_second, const phynet::math::Vector2& i_contactNormal, const Real i_penetration, const Real i_restitution);

	void Resolve(const Real i_duration);

private:
	void ResolveVelocity(const Real i_duration);
	void ResolvePosition(const Real i_duration);

	RigidBody2d* m_particles[2];
	phynet::math::Vector2 m_contactNormal;
	Real m_penetration;
	Real m_restitution;
};

}}//namespaces