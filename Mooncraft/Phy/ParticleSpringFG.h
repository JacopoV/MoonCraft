#pragma once

#include "ParticleForceGenerator.h"

namespace phynet{
namespace phy{

template<int Dim>
class ParticleSpringFG : public ParticleForceGenerator<Dim>
{
public:
	ParticleSpringFG();
	ParticleSpringFG(ParticleType* i_particle, const Real i_k, const Real i_lenght);
	void Init(ParticleType* i_particle, const Real i_k, const Real i_lenght);
	
	virtual void ApplyForce(ParticleType* i_particle);

private:
	ParticleType* m_particle;
	Real m_k;
	Real m_lenght;
};

template<int Dim>
class ParticleAnchoredSpringFG : public ParticleForceGenerator<Dim>
{
public:
	ParticleAnchoredSpringFG();
	ParticleAnchoredSpringFG(const VectorType& i_anchor, const Real i_k, const Real i_lenght);
	void Init(const VectorType& i_anchor, const Real i_k, const Real i_lenght);
	
	virtual void ApplyForce(ParticleType* i_particle);

private:
	VectorType m_anchor;
	Real m_k;
	Real m_lenght;
};

}} // namespaces

#include "ParticleSpringFG.inl"

