#pragma once

#include "math/MathUtils.h"
#include "math/MathTypes.h"
#include "Particle.h"
#include <cassert>

namespace phynet{
namespace phy{

template<int Dim>
class ParticleContact
{
public:
	typedef typename math::Vector<Dim>::Type VectorType;
	typedef Particle<Dim> ParticleType;
	ParticleContact();
	ParticleContact(ParticleType* i_first, ParticleType* i_second, const VectorType& i_contactNormal, const Real i_penetration, const Real i_restitution);
	void Init(ParticleType* i_first, ParticleType* i_second, const VectorType& i_contactNormal, const Real i_penetration, const Real i_restitution);

	void Resolve(const Real i_duration);

private:
	void ResolveVelocity(const Real i_duration);
	void ResolvePosition(const Real i_duration);

	ParticleType* m_particles[2];
	VectorType m_contactNormal;
	Real m_penetration;
	Real m_restitution;
};

}} // namespaces

#include "ParticleContact.inl"
