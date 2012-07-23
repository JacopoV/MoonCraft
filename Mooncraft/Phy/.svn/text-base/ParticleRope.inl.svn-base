namespace phynet{
namespace phy{

template<int Dim>
inline ParticleRope<Dim>::ParticleRope()
	:ParticleLink<Dim>()
	,m_restitution(1.0f)
{
}

template<int Dim>
inline void ParticleRope<Dim>::Init(const Real i_lenght, ParticleType* i_first, ParticleType* i_second, const Real i_restitution)
{
	LinkInit(i_lenght, i_first, i_second);
	m_restitution = i_restitution;
}

template<int Dim>
inline int ParticleRope<Dim>::AddContact(ContactType* o_contact)
{
	Real lenght = GetCurrentLenght();
	if(math::LessThanOrEqual(lenght, m_lenght))
		return 0;
	VectorType normal = m_secondParticle->GetPosition() - m_firstParticle->GetPosition();
	normal.Normalize();
	o_contact->Init(m_firstParticle, m_secondParticle, normal, lenght-m_lenght, m_restitution);
	return 1;
}

template<int Dim>
inline ParticleAnchoredRope<Dim>::ParticleAnchoredRope()
	:ParticleAnchoredLink<Dim>()
	,m_restitution(1.0f)
{
}

template<int Dim>
inline void ParticleAnchoredRope<Dim>::Init(const Real i_lenght, ParticleType* i_first, const VectorType& i_anchor, const Real i_restitution)
{
	AnchoredLinkInit(i_lenght, i_first, i_anchor);
	m_restitution = i_restitution;
}

template<int Dim>
inline int ParticleAnchoredRope<Dim>::AddContact(ContactType* o_contact)
{
	Real lenght = GetCurrentLenght();
	if(math::LessThanOrEqual(lenght, m_lenght))
		return 0;

	VectorType normal =  m_anchor - m_firstParticle->GetPosition();
	normal.Normalize();
	o_contact->Init(m_firstParticle, 0, normal, lenght-m_lenght, m_restitution);
	return 1;
}

}} // namespaces
