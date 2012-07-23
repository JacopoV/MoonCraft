namespace phynet{
namespace phy{

template<int Dim>
inline ParticleContact<Dim>::ParticleContact()
{
}

template<int Dim>
inline ParticleContact<Dim>::ParticleContact(ParticleType* i_first, ParticleType* i_second, const VectorType& i_contactNormal, const Real i_penetration, const Real i_restitution)
	:m_contactNormal(i_contactNormal)
	,m_penetration(i_penetration)
	,m_restitution(i_restitution)
{
	m_particles[0] = i_first;
	m_particles[1] = i_second;
}

template<int Dim>
inline void ParticleContact<Dim>::Init(ParticleType* i_first, ParticleType* i_second, const VectorType& i_contactNormal, const Real i_penetration, const Real i_restitution)
{
	m_contactNormal = i_contactNormal;
	m_penetration = i_penetration;
	m_restitution = i_restitution;
	m_particles[0] = i_first;
	m_particles[1] = i_second;
}

template<int Dim>
inline void ParticleContact<Dim>::Resolve(const Real i_duration)
{
	ResolveVelocity(i_duration);
	ResolvePosition(i_duration);
}

template<int Dim>
inline void ParticleContact<Dim>::ResolveVelocity(const Real /*i_duration*/)
{
	VectorType vel = m_particles[0]->GetVelocity();
	if(m_particles[1])
		vel -= m_particles[1]->GetVelocity();
	const Real vs = Dot(vel, m_contactNormal);
	
	if(math::GreaterThanOrEqual(vs, 0.0f))
		return;

	const Real mass0 = m_particles[0]->GetMass();
	const Real mass1 = (m_particles[1] ? m_particles[1]->GetMass() : mass0 * 1000.0f);
	const Real totalMass = mass0 + mass1;
	
	if(math::AreEqual(totalMass, 0.0f))
		return;

	const Real newvs = -m_restitution * vs;
	const Real deltavs = newvs - vs;
	const Real deltavs0 = deltavs * mass1/totalMass;
	const Real deltavs1 = deltavs * mass0/totalMass;

	const Real impulse0 = deltavs0 * mass0;
	const Real impulse1 = -deltavs1 * mass1;
	assert(!m_particles[1] || math::AreEqual(impulse0, -impulse1));

	m_particles[0]->AddImpulse(m_contactNormal * impulse0);
	if(m_particles[1])
		m_particles[1]->AddImpulse(m_contactNormal * impulse1);
}

template<int Dim>
inline void ParticleContact<Dim>::ResolvePosition(const Real /*i_duration*/)
{
	if(math::LessThanOrEqual(m_penetration, 0.0f))
		return;

	const Real invMass0 = m_particles[0]->GetInvMass();
	const Real invMass1 = (m_particles[1] ? m_particles[1]->GetInvMass() : 0.0f);
	const Real totalInvMass = invMass0 + invMass1;
	
	if(math::AreEqual(totalInvMass, 0.0f))
		return;

	m_particles[0]->SetPosition(
		m_particles[0]->GetPosition() + 
		m_contactNormal * (m_penetration * (invMass0 / totalInvMass)));

	if(m_particles[1])
		m_particles[1]->SetPosition(
			m_particles[1]->GetPosition() - 
			m_contactNormal * (m_penetration * (invMass1 / totalInvMass)));
}

}} // namespaces

