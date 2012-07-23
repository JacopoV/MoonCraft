#pragma once

#include "math/MathUtils.h"
#include "math/MathTypes.h"

namespace phynet{
namespace phy{

/*	the Particle class template can be instantiated with Vector2 or Vector3 in order to have a 2D or 3D Particle*/
template<int Dim>
class Particle
{
public:
	typedef typename math::Vector<Dim>::Type VectorType;

	Particle();
	Particle(const Real i_mass, const Real i_radius, const Real i_damping, const Real i_elasticity, const VectorType& i_pos, const VectorType& i_vel);
	void Init(const Real i_mass, const Real i_radius, const Real i_damping, const Real i_elasticity, const VectorType& i_pos, const VectorType& i_vel);
	void SetPosition(const VectorType& i_pos);
	void SetVelocity(const VectorType& i_vel);
	void SetMass(const Real i_mass);
	void SetDamping(const Real i_damping);
	void SetElasticity(const Real i_elasticity);
	const VectorType& GetPosition() const;
	const VectorType& GetVelocity() const;
	const Real GetInvMass() const;
	const Real GetMass() const;
	const Real GetRadius() const;
	const Real GetDamping() const;
	const Real GetElasticity() const;
	const bool HasInfiniteMass() const;

	void AddForce(const VectorType& i_force);
	void AddImpulse(const VectorType& i_impulse);

	void Integrate(const Real i_elapsedTime);

private:
	VectorType m_position;
	VectorType m_velocity;
	VectorType m_acceleration;
	VectorType m_totalForce;
	Real m_mass;
	Real m_inverseMass;
	Real m_damping;
	Real m_radius;
	Real m_elasticity;
};

}} // namespaces

#include "Particle.inl"

