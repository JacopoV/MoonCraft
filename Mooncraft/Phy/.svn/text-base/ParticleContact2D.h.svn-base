#pragma once

namespace phynet
{
namespace phy
{

template<typename VectorType>
class ParticleContact
{
public:
	typedef Particle<VectorType> ParticleType;
	ParticleContact(ParticleType* i_first, ParticleType* i_second, const VectorType& i_contactNormal, const Real i_penetration, const Real i_restitution);

	void Resolve(const Real i_duration);

private:
	void ResolveVelocity(const Real i_duration);
	void ResolvePosition(const Real i_duration);

	ParticleType* m_particles[2];
	VectorType m_contactNormal;
	Real m_penetration;
	Real m_restitution;
};

template<typename VectorType>
inline ParticleContact<VectorType>::ParticleContact(ParticleType* i_first, ParticleType* i_second, const VectorType& i_contactNormal, const Real i_penetration, const Real i_restitution)
	:m_contactNormal(i_contactNormal)
	,m_penetration(i_penetration)
	,m_restitution(i_restitution)
{
	m_particles[0] = i_first;
	m_particles[1] = i_second;
}

template<typename VectorType>
inline void ParticleContact::Resolve(const Real i_duration)
{
	ResolveVelocity(i_duration);
	ResolvePosition(i_duration);
}

template<typename VectorType>
inline void ParticleContact::ResolveVelocity(const Real /*i_duration*/)
{
	const Real vs = Dot(m_particles[0]->GetVelocity() - m_particles[1]->GetVelocity(), m_contactNormal);
	
	if(math::GreaterThanOrEqual(vs, 0.0f))
		return;

	const Real mass0 = m_particles[0]->GetMass();
	const Real mass1 = m_particles[1]->GetMass();
	const Real totalMass = mass0 + mass1;
	
	if(math::AreEqual(totalMass, 0.0f))
		return;

	const Real newvs = -m_restitution * vs;
	const Real deltavs = newvs - vs;
	const Real deltavs0 = deltavs * mass1/totalMass;
	const Real deltavs1 = deltavs * mass0/totalMass;

	const Real impulse0 = deltavs0 * mass0;
	const Real impulse1 = -deltavs1 * mass1;
	assert(math::AreEqual(impulse0, -impulse1));

	m_particles[0]->AddImpulse(m_contactNormal * impulse0);
	m_particles[1]->AddImpulse(m_contactNormal * impulse1);
}

template<typename VectorType>
inline void ParticleContact::ResolvePosition(const Real /*i_duration*/)
{
	if(math::LessThanOrEqual(m_penetration, 0.0f))
		return;

	const Real invMass0 = m_particles[0]->GetInvMass();
	const Real invMass1 = m_particles[1]->GetInvMass();
	const Real totalInvMass = invMass0 + invMass1;
	
	if(math::AreEqual(totalInvMass, 0.0f))
		return;

	m_particles[0]->SetPosition(
		m_particles[0]->GetPosition() + 
		m_contactNormal * (m_penetration * (invMass0 / totalInvMass)));

	m_particles[1]->SetPosition(
		m_particles[1]->GetPosition() - 
		m_contactNormal * (m_penetration * (invMass1 / totalInvMass)));
}
} //namespace phy
} // namespace phynet


