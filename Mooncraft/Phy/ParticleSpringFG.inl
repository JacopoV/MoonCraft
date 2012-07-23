namespace phynet{
namespace phy{

template<int Dim>
inline ParticleSpringFG<Dim>::ParticleSpringFG()
{
	Init(0,0,0);
}

template<int Dim>
inline ParticleSpringFG<Dim>::ParticleSpringFG(ParticleType* i_particle, const Real i_k, const Real i_lenght)
{
	Init(i_particle, i_k, i_lenght);
}

template<int Dim>
inline void ParticleSpringFG<Dim>::Init(ParticleType* i_particle, const Real i_k, const Real i_lenght)
{
	m_particle = i_particle;
	m_k = i_k;
	m_lenght = i_lenght;
}

template<int Dim>
inline void ParticleSpringFG<Dim>::ApplyForce(ParticleType* i_particle)
{
	const VectorType dist = i_particle->GetPosition() - m_particle->GetPosition();
	const Real lenght = dist.Magnitude();
	const Real intensity = m_k * (lenght - m_lenght);
	VectorType force = -dist;
	force.Normalize();
	force *= intensity;
	i_particle->AddForce(force);
}

template<int Dim>
inline ParticleAnchoredSpringFG<Dim>::ParticleAnchoredSpringFG()
{
	Init(VectorType::ZERO,0,0);
}

template<int Dim>
inline ParticleAnchoredSpringFG<Dim>::ParticleAnchoredSpringFG(const VectorType& i_anchor, const Real i_k, const Real i_lenght)
{
	Init(i_anchor, i_k, i_lenght);
}

template<int Dim>
inline void ParticleAnchoredSpringFG<Dim>::Init(const VectorType& i_anchor, const Real i_k, const Real i_lenght)
{
	m_anchor = i_anchor;
	m_k = i_k;
	m_lenght = i_lenght;
}

template<int Dim>
inline void ParticleAnchoredSpringFG<Dim>::ApplyForce(ParticleType* i_particle)
{
	const VectorType dist = i_particle->GetPosition() - m_anchor;
	const Real lenght = dist.Magnitude();
	const Real intensity = m_k * (lenght - m_lenght);
	VectorType force = -dist;
	force.Normalize();
	force *= intensity;
	i_particle->AddForce(force);
}

}} // namespaces

