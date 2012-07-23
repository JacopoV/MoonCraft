#pragma once

#include "ParticleForceGenerator.h"

namespace phynet{
namespace phy{

template<int Dim>
class ParticleGravityFG : public ParticleForceGenerator<Dim>
{
public:
	explicit ParticleGravityFG(const VectorType& i_gravityAcceleration = VectorType::ZERO)
	{
		SetGravityAcceleration(i_gravityAcceleration);
	}

	void SetGravityAcceleration(const VectorType& i_gravityAcceleration)
	{
		m_gravity = i_gravityAcceleration;
	}
	
	virtual void ApplyForce(ParticleType* i_particle)
	{
		if( (i_particle) && (!i_particle->HasInfiniteMass()) )
			i_particle->AddForce(m_gravity * i_particle->GetMass());
	}

private:
	VectorType m_gravity;
};


}} // namespaces


/*Temporary code... keep here, maybe it will useful*/

//class ParticleSpotGravityFG : public ParticleForceGenerator
//{
//public:
//	ParticleSpotGravityFG(const Real i_mass = 0.0f, const Vector2& i_location = Vector2::ZERO, const Real i_gravityConstant = 0.0f);
//	void Set(const Real i_mass, const Vector2& i_location, const Real i_gravityConstant);
//	const Real GetMass() const;
//	const Real GetGravityConstant() const;
//	const Vector2& GetLocation() const;
//	
//	virtual void ApplyForce(Particle* i_particle);
//
//private:
//	Vector2 m_location;
//	Real m_gravityConstant;
//	Real m_mass;
//};
//
//class ParticleParticleGravityFG : public ParticleForceGenerator
//{
//public:
//	ParticleParticleGravityFG(Particle* const i_particle = 0, const Real i_gravityConstant = 0.0f);
//	void Set(Particle* const i_particle, const Real i_gravityConstant);
//	const Real GetGravityConstant() const;
//	Particle* const GetLocation() const;
//	
//	virtual void ApplyForce(Particle* i_particle);
//
//private:
//	Real m_gravityConstant;
//	Particle* m_location;
//};
//
//inline ParticleSpotGravityFG::ParticleSpotGravityFG(const Real i_mass, const Vector2& i_location, const Real i_gravityConstant)
//{
//	Set(i_mass, i_location, i_gravityConstant);
//}
//
//inline void ParticleSpotGravityFG::Set(const Real i_mass, const Vector2& i_location, const Real i_gravityConstant)
//{
//	m_mass = i_mass;
//	m_location = i_location;
//	m_gravityConstant = i_gravityConstant;
//}
//
//inline const Real ParticleSpotGravityFG::GetMass() const
//{
//	return m_mass;
//}
//
//inline const Real ParticleSpotGravityFG::GetGravityConstant() const
//{
//	return m_gravityConstant;
//}
//
//inline const Vector2& ParticleSpotGravityFG::GetLocation() const
//{
//	return m_location;
//}
//
//inline void ParticleSpotGravityFG::ApplyForce(Particle* i_particle)
//{
//	if( (i_particle) && (!i_particle->HasInfiniteMass()) )
//	{
//		Vector2 force = m_location;
//		force -= i_particle->GetPosition();
//		Real den = force.Magnitude();
//		den *= den*den; //pow(den, 3)
//
//		Real forceIntensity = m_gravityConstant * i_particle->GetMass() * m_mass /den;
//		force *= forceIntensity;
//		i_particle->AddForce(force);
//	}
//}
//
//inline ParticleParticleGravityFG::ParticleParticleGravityFG(Particle* const i_particle, const Real i_gravityConstant)
//{
//	Set(i_particle, i_gravityConstant);
//}
//
//inline void ParticleParticleGravityFG::Set(Particle* const i_particle, const Real i_gravityConstant)
//{
//	m_location = i_particle;
//	m_gravityConstant = i_gravityConstant;
//}
//
//inline const Real ParticleParticleGravityFG::GetGravityConstant() const
//{
//	return m_gravityConstant;
//}
//
//inline Particle* const ParticleParticleGravityFG::GetLocation() const
//{
//	return m_location;
//}
//	
//inline void ParticleParticleGravityFG::ApplyForce(Particle* i_particle)
//{
//	if( (i_particle) && (!i_particle->HasInfiniteMass()) )
//	{
//		Vector2 force = m_location->GetPosition();
//		force -= i_particle->GetPosition();
//		Real den = force.Magnitude();
//		den *= den*den; //pow(den, 3)
//
//		Real forceIntensity = m_gravityConstant * i_particle->GetMass() * m_location->GetMass() /den;
//		force *= forceIntensity;
//		i_particle->AddForce(force);
//	}
//}
//
