#pragma once

#include "Particle.h"
#include "ParticleForceGenerator.h"

namespace phynet{
namespace phy{

template<int Dim>
class ParticleWindFG : public ParticleForceGenerator<Dim>
{
public:
	explicit ParticleWindFG(const VectorType& i_baseForce = VectorType::ZERO(), const Real i_heightFactor = 0.0f)
	{
		Set(i_baseForce, i_heightFactor);
	}
	
	void Set(const VectorType& i_baseForce, const Real i_heightFactor)
	{
		m_baseForce = i_baseForce;
		m_heightFactor = i_heightFactor;
	}

	const VectorType& GetBaseWindForce() const
	{
		return m_baseForce;
	}

	const Real GetHeightFactor() const
	{
		return m_heightFactor;
	}

	virtual void ApplyForce(ParticleType* i_particle)
	{
		if( (i_particle) && (!i_particle->HasInfiniteMass()) )
		{
			const Real particleHeight = i_particle->GetPosition().Y();
			i_particle->AddForce(m_baseForce * (1 + (m_heightFactor * particleHeight)));
		}
	}

private:
	VectorType m_baseForce;
	Real m_heightFactor;
};

}} // namespaces
