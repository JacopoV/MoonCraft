namespace phynet{
namespace phy{

inline void ParticleEngine2D::EnableParticleCollisions(const bool i_enable)
{
	m_particleCollisionsEnabled = i_enable;
}

inline void ParticleEngine2D::EnableWorldCollisions(const bool i_enable)
{
	m_worldCollisionsEnabled = i_enable;
}

inline void ParticleEngine2D::EnableAllCollisions(const bool i_enable)
{
	EnableParticleCollisions(i_enable);
	EnableWorldCollisions(i_enable);
}

inline bool ParticleEngine2D::IsParticleCollisionsEnabled() const
{
	return m_particleCollisionsEnabled;
}

inline bool ParticleEngine2D::IsWorldCollisionsEnabled() const
{
	return m_worldCollisionsEnabled;
}

inline bool ParticleEngine2D::IsAllCollisionsEnabled() const
{
	return IsWorldCollisionsEnabled() && IsParticleCollisionsEnabled();
}

inline const ParticleWorld2D& ParticleEngine2D::GetWorld() const
{
	return m_world;
}

inline ParticleWorld2D& ParticleEngine2D::GetWorld()
{
	return m_world;
}

inline const Boundary2D& ParticleEngine2D::GetWorldBoundary() const
{
	return m_staticWorldOutPoly;
}

inline const ParticleEngine2D::Boundaries& ParticleEngine2D::GetInternalBoundaries() const
{
	return m_staticWorldInPoly;
}

inline void ParticleEngine2D::SetWorldBoundary(const Boundary2D& i_boundary)
{
	m_staticWorldOutPoly = i_boundary;
}

inline void ParticleEngine2D::AddInternalBoundary(const Boundary2D& i_boundary)
{
	m_staticWorldInPoly.push_back(i_boundary);
}

inline void ParticleEngine2D::ClearInternalBoundaries()
{
	m_staticWorldInPoly.clear();
}

}} // namespaces

