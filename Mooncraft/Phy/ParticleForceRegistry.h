#pragma once

#include "ParticleForceGenerator.h"
#include "common/Utilities.h"

#include <vector>
#include <algorithm>

namespace phynet{
namespace phy{

template<int Dim>
class ParticleForceRegistry
{
public:
	typedef Particle<Dim> ParticleType;
	typedef ParticleForceGenerator<Dim> ForceType;
	typedef std::pair<ForceType*, ParticleType*> PairFP;
	typedef std::vector< PairFP > Pairs;

	void AddPair(ForceType* const i_force, ParticleType* const i_particle)
	{
		//TODO: check if the pair is present
		m_pairs.push_back(PairFP(i_force, i_particle));
	}

	void RemovePair(ForceType* const i_force, ParticleType* const i_particle)
	{
		const PairFP toBeRemoved(i_force, i_particle);
		erase_unordered(m_pairs, toBeRemoved);
	}

	void RemoveForce(ForceType* const i_force);
	void RemoveParticle(ParticleType* const i_particle);
	
	void Clear()
	{
		m_pairs.clear();
	}

	void UpdateForces()
	{
		for(Pairs::iterator it = m_pairs.begin(); it != m_pairs.end(); ++it)
			it->first->ApplyForce(it->second);
	}

private:
	Pairs m_pairs;
};

template<int Dim>
struct SameForce
{
	explicit SameForce(ParticleForceGenerator<Dim>* const i_force)
		:m_force(i_force)
	{
	}
	bool operator()(const typename ParticleForceRegistry<Dim>::PairFP& i_pairFP) const
	{
		return m_force == i_pairFP.first;
	}
	ParticleForceGenerator<Dim>* m_force;
};

template<int Dim>
struct SameParticle
{
	explicit SameParticle(Particle<Dim>* const i_particle)
		:m_particle(i_particle)
	{
	}
	bool operator()(const typename ParticleForceRegistry<Dim>::PairFP& i_pairFP) const
	{
		return m_particle == i_pairFP.second;
	}
	Particle<Dim>* m_particle;
};

template<int Dim>
inline void ParticleForceRegistry<Dim>::RemoveForce(ForceType* const i_force)
{
	RemoveAll_unordered(m_pairs, SameForce<Dim>(i_force));
}

template<int Dim>
inline void ParticleForceRegistry<Dim>::RemoveParticle(ParticleType* const i_particle)
{
	RemoveAll_unordered(m_pairs, SameParticle<Dim>(i_particle));
}
	

}} // namespaces
