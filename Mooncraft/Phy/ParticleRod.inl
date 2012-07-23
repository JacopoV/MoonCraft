namespace phynet{
namespace phy{

template<int Dim>
inline ParticleRod<Dim>::ParticleRod()
{
}

template<int Dim>
inline void ParticleRod<Dim>::Init(const Real i_lenght, ParticleType* i_first, ParticleType* i_second)
{
	LinkInit(i_lenght, i_first, i_second);
}

template<int Dim>
inline void ParticleRod<Dim>::Init(ParticleType* i_first, ParticleType* i_second)
{
	LinkInit(math::Distance(i_first->GetPosition(), i_second->GetPosition()), i_first, i_second);
}

template<int Dim>
inline int ParticleRod<Dim>::AddContact(ContactType* o_contact)
{
	Real lenght = GetCurrentLenght();
	if(math::AreEqual(lenght, m_lenght))
		return 0;

	VectorType normal = m_secondParticle->GetPosition() - m_firstParticle->GetPosition();
	normal.Normalize();
	
	if(lenght > m_lenght)
		o_contact->Init(m_firstParticle, m_secondParticle, normal, lenght-m_lenght, 0.0f);
	else
		o_contact->Init(m_firstParticle, m_secondParticle, -normal, m_lenght-lenght, 0.0f);
	return 1;
}

template<int Dim>
inline ParticleAnchoredRod<Dim>::ParticleAnchoredRod()
{
}

template<int Dim>
inline void ParticleAnchoredRod<Dim>::Init(const Real i_lenght, ParticleType* i_first, const VectorType& i_anchor)
{
	AnchoredLinkInit(i_lenght, i_first, i_anchor);
}

template<int Dim>
inline void ParticleAnchoredRod<Dim>::Init(ParticleType* i_first, const VectorType& i_anchor)
{
	AnchoredLinkInit(math::Distance(i_first->GetPosition(), i_anchor), i_first, i_anchor);
}

template<int Dim>
inline int ParticleAnchoredRod<Dim>::AddContact(ContactType* o_contact)
{
	Real lenght = GetCurrentLenght();
	if(math::AreEqual(lenght, m_lenght))
		return 0;

	VectorType normal =  m_anchor - m_firstParticle->GetPosition();
	normal.Normalize();
	
	if(lenght > m_lenght)
		o_contact->Init(m_firstParticle, 0, normal, lenght-m_lenght, 0.0f);
	else
		o_contact->Init(m_firstParticle, 0, -normal, m_lenght-lenght, 0.0f);
	return 1;
}

}} // namespaces
