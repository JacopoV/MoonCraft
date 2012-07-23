#pragma once

#include "ParticleForceGenerator.h"

namespace phynet{
namespace phy{

template<int Dim>
class ParticleDragFG : public ParticleForceGenerator<Dim>
{
public:
	ParticleDragFG(const Real i_k1, const Real i_k2)
		:m_k1(i_k1)
		,m_k2(i_k2)
	{
	}
	
	virtual void ApplyForce(ParticleType* i_particle)
	{
		const VectorType& vel = i_particle->GetVelocity();
		VectorType force = -vel.GetNormalized();
		force *= (m_k1 * vel.Magnitude()) + (m_k2 * vel.SquareMagnitude());
		i_particle->AddForce(force);
	}

private:
	Real m_k1;
	Real m_k2;
};


}} // namespaces

