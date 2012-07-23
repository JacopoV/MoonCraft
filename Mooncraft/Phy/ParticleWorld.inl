namespace phynet{
namespace phy{

template<int Dim>
inline ParticleWorld<Dim>::ParticleWorld()
{
	Init();
}

template<int Dim>
inline ParticleWorld<Dim>::~ParticleWorld()
{
	Clear();
}

template<int Dim>
inline const typename ParticleWorld<Dim>::Particles& ParticleWorld<Dim>::GetParticles() const
{
	return m_particles;
}

template<int Dim>
inline void ParticleWorld<Dim>::AddParticleUnchecked(ParticleType* const i_particle)
{
	m_particles.push_back(i_particle);
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveAllParticles()
{
	RemoveAllForcesOnParticles();
	m_particles.clear();
}

template<int Dim>
inline const typename ParticleWorld<Dim>::Forces& ParticleWorld<Dim>::GetForces() const
{
	return m_forces;
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveAllForces()
{
	m_forces.clear();
	RemoveAllForcesOnParticles();
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveAllForcesOnParticles()
{
	m_registry.Clear();
}

template<int Dim>
inline void ParticleWorld<Dim>::AddForceOnParticle(ForceType* i_force, ParticleType* i_particle)
{
	m_registry.AddPair(i_force, i_particle);
}

template<int Dim>
inline void ParticleWorld<Dim>::AddForceOnParticles(ForceType* const i_force, ParticleType* const i_particles, const int i_numParticles)
{
	for(int i=0; i<i_numParticles; ++i)
		AddForceOnParticle(i_force, i_particles+i);
}

template<int Dim>
inline void ParticleWorld<Dim>::AddForceOnParticles(ForceType* const i_force, ParticleType** const i_particles, const int i_numParticles)
{
	for(int i=0; i<i_numParticles; ++i)
		AddForceOnParticle(i_force, *(i_particles+i));
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveForceOnParticle(ForceType* i_force, ParticleType* i_particle)
{
	m_registry.RemovePair(i_force, i_particle);
}

template<int Dim>
inline void ParticleWorld<Dim>::Init()
{
	Clear();
}

template<int Dim>
inline void ParticleWorld<Dim>::Clear()
{
	m_currentTime = 0.f;

	m_particles.clear();
	m_forces.clear();
	m_registry.Clear();
	m_links.clear();
}

template<int Dim>
inline void ParticleWorld<Dim>::AddParticles(ParticleType* const i_particles, const int i_numParticles, const bool i_checked)
{
	assert(i_particles);

	if(i_checked)
		for(int i=0; i< i_numParticles; ++i)
			AddParticle(i_particles + i);
	else
		for(int i=0; i< i_numParticles; ++i)
			AddParticleUnchecked(i_particles + i);
}

template<int Dim>
inline void ParticleWorld<Dim>::AddParticles(ParticleType** const i_particles, const int i_numParticles, const bool i_checked)
{
	assert(i_particles);

	if(i_checked)
		for(int i=0; i< i_numParticles; ++i)
			AddParticle(*(i_particles + i));
	else
		for(int i=0; i< i_numParticles; ++i)
			AddParticleUnchecked(*(i_particles + i));
}

template<int Dim>
inline void ParticleWorld<Dim>::AddParticle(ParticleType* const i_particle)
{
	InsertUnique(i_particle, m_particles);
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveParticle(ParticleType* i_particle)
{
	Particles::iterator i = std::find(m_particles.begin(), m_particles.end(), i_particle);
	if (i != m_particles.end())
	{
		ParticleType* particle = *i;
		m_registry.RemoveParticle(particle);
		erase_unordered(m_particles, particle);
		RemoveAll_unordered(m_links, [=](LinkType* l) { return l->GetParticle(0) == particle || l->GetParticle(1) == particle;});
	}
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveParticle(const UInt i_particleIndex)
{
	ParticleType* particle = m_particles[i_particleIndex];
	m_registry.RemoveParticle(particle);
	erase_unordered(m_particles, m_particles.begin() + i_particleIndex);
	RemoveAll_unordered(m_links, [=](LinkType* l) { return l->GetParticle(0) == particle || l->GetParticle(1) == particle;});
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveParticles(ParticleType* const i_particles, const int i_numParticles)
{
	for(auto i=0; i<i_numParticles; ++i)
		RemoveParticle(i_particles+i);
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveParticles(ParticleType** const i_particles, const int i_numParticles)
{
	for(auto i=0; i<i_numParticles; ++i)
		RemoveParticle(*(i_particles+i));
}

template<int Dim>
inline void ParticleWorld<Dim>::AddForce(ForceType* const i_force)
{
	InsertUnique(i_force, m_forces);
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveForce(ForceType* const i_force)
{
	Forces::iterator i = std::find(m_forces.begin(), m_forces.end(), i_force);
	if (i != m_forces.end())
	{
		m_registry.RemoveForce(*i);
		m_forces.erase(i);
	}
}

template<int Dim>
inline void ParticleWorld<Dim>::AddLink(LinkType* const i_link)
{
	InsertUnique(i_link, m_links);
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveLink(LinkType* const i_link)
{
	erase_unordered(m_links, i_link);
}

template<int Dim>
inline void ParticleWorld<Dim>::RemoveAllLinks()
{
	m_links.clear();
}

template<int Dim>
inline const typename ParticleWorld<Dim>::Links& ParticleWorld<Dim>::GetLinks() const
{
	return m_links;
}

template<int Dim>
inline void ParticleWorld<Dim>::Update(const Real i_timeElapsed)
{
	// time update
	m_currentTime += i_timeElapsed;

	// force update
	m_registry.UpdateForces();

	// Integration
	for(size_t i=0;i< m_particles.size(); ++i)
		m_particles[i]->Integrate(i_timeElapsed);
}

}} // namespaces
