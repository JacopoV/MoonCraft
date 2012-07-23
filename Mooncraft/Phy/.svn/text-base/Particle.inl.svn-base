namespace phynet{
namespace phy{

template<int Dim>
inline Particle<Dim>::Particle()
{
	Init(0.0f, 0.1f, 1.0f, 0.0f, VectorType::ZERO(), VectorType::ZERO());
}

template<int Dim>
inline Particle<Dim>::Particle(const Real i_mass, const Real i_radius, const Real i_damping, const Real i_elasticity, const VectorType& i_pos, const VectorType& i_vel)
{
	Init(i_mass, i_radius, i_damping, i_elasticity, i_pos, i_vel);
}

template<int Dim>
inline void Particle<Dim>::Init(const Real i_mass, const Real i_radius, const Real i_damping, const Real i_elasticity, const VectorType& i_pos, const VectorType& i_vel)
{
	m_radius = i_radius;
	m_damping = i_damping;
	m_elasticity = i_elasticity;
	
	m_position = i_pos;
	m_velocity = i_vel;

	m_acceleration.Zero();
	m_totalForce.Zero();

	SetMass(i_mass);
}

template<int Dim>
inline void Particle<Dim>::SetPosition(const VectorType& i_pos)
{
	m_position = i_pos;
}

template<int Dim>
inline void Particle<Dim>::SetVelocity(const VectorType& i_vel)
{
	m_velocity = i_vel;
}

template<int Dim>
inline void Particle<Dim>::SetMass(const Real i_mass)
{
	m_mass = i_mass;
	m_inverseMass = math::AreEqual(i_mass, 0.0f) ? 0.0f : (1.0f/i_mass);
}

template<int Dim>
inline void Particle<Dim>::SetDamping(const Real i_damping)
{
	m_damping = i_damping;
}

template<int Dim>
inline void Particle<Dim>::SetElasticity(const Real i_elasticity)
{
	m_elasticity = i_elasticity;
}

template<int Dim>
inline const typename Particle<Dim>::VectorType& Particle<Dim>::GetPosition() const
{
	return m_position;
}

template<int Dim>
inline const typename Particle<Dim>::VectorType& Particle<Dim>::GetVelocity() const
{
	return m_velocity;
}

template<int Dim>
inline const Real Particle<Dim>::GetInvMass() const
{
	return m_inverseMass;
}

template<int Dim>
inline const Real Particle<Dim>::GetMass() const
{
	return m_mass;
}

template<int Dim>
inline const Real Particle<Dim>::GetRadius() const
{
	return m_radius;
}

template<int Dim>
inline const Real Particle<Dim>::GetDamping() const
{
	return m_damping;
}

template<int Dim>
inline const Real Particle<Dim>::GetElasticity() const
{
	return m_elasticity;
}

template<int Dim>
inline void Particle<Dim>::AddForce(const VectorType& i_force)
{
	m_totalForce += i_force;
}

template<int Dim>
inline void Particle<Dim>::AddImpulse(const VectorType& i_impulse)
{
	m_velocity += i_impulse * GetInvMass();
}

template<int Dim>
inline const bool Particle<Dim>::HasInfiniteMass() const
{
	return math::AreEqual(GetInvMass(), 0.0f);
}

template<int Dim>
inline void Particle<Dim>::Integrate(const Real i_elapsedTime)
{
	// calculate acceleration
	m_acceleration = m_totalForce * m_inverseMass;

	// calculate position
	m_position += m_velocity * i_elapsedTime; // m_acceleration * i_elapsedTime * i_elapsedTime * 0.5f
	
	// calculate velocity
	m_velocity = m_damping*m_velocity + m_acceleration * i_elapsedTime;

	// clear forces
	m_totalForce.Zero();
}

}} // namespaces
