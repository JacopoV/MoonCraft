#pragma once

#include "WorldBase.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "ParticleLink.h"
#include "common/Utilities.h"
#include "math/MathUtils.h"

#include <vector>
#include <algorithm>
#include <cassert>

namespace phynet{
namespace phy{
	
template<int Dim>
class ParticleWorld : public WorldBase
{
public:
	typedef typename math::Vector<Dim>::Type VectorType;
	typedef Particle<Dim> ParticleType;
	typedef ParticleForceGenerator<Dim> ForceType;
	typedef ParticleForceRegistry<Dim> RegistryType;
	typedef ParticleBaseLink<Dim> LinkType;

	typedef std::vector<ParticleType*> Particles;
	typedef std::vector<ForceType*> Forces;
	typedef std::vector<LinkType*> Links;

	ParticleWorld();
	virtual ~ParticleWorld();
	void Init();
	void Clear();
	
	//particle management
	const Particles& GetParticles() const;
	void AddParticleUnchecked(ParticleType* const i_particle);
	void AddParticle(ParticleType* const i_particle);
	void AddParticles(ParticleType* const i_particles, const int i_numParticles, const bool i_checked = false);
	void AddParticles(ParticleType** const i_particles, const int i_numParticles, const bool i_checked = false);
	void RemoveParticle(ParticleType* const i_particle);
	void RemoveParticles(ParticleType* const i_particles, const int i_numParticles);
	void RemoveParticles(ParticleType** const i_particles, const int i_numParticles);
	void RemoveParticle(const UInt i_particleIndex);
	void RemoveAllParticles();

	//force management
	const Forces& GetForces() const;
	void AddForce(ForceType* const i_force);
	void RemoveForce(ForceType* const i_force);
	void RemoveAllForces();

	//force/particle pairing
	void AddForceOnParticle(ForceType* const i_force, ParticleType* const i_particle);
	void AddForceOnParticles(ForceType* const i_force, ParticleType* const i_particles, const int i_numParticles);
	void AddForceOnParticles(ForceType* const i_force, ParticleType** const i_particles, const int i_numParticles);
	void RemoveForceOnParticle(ForceType* const i_force, ParticleType* const i_particle);
	void RemoveAllForcesOnParticles();

	//links
	const Links& GetLinks() const;
	void AddLink(LinkType* const i_link);
	void RemoveLink(LinkType* const i_link);
	void RemoveAllLinks();
	
	virtual void Update(const Real i_timeelapsed);

private:
	Particles m_particles;
	Forces m_forces;
	RegistryType m_registry;

	Links m_links;
};

} // namespace phy
} // namespace phynet

#include "ParticleWorld.inl"
