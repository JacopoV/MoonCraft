#pragma once

#include "Particle.h"

namespace phynet{
namespace phy{

template<int Dim>
class ParticleForceGenerator
{
public:
	typedef Particle<Dim> ParticleType;
	typedef typename ParticleType::VectorType VectorType;

	virtual ~ParticleForceGenerator(){}
	virtual void ApplyForce(ParticleType* i_particle) = 0;
};

}} // namespace phynet
