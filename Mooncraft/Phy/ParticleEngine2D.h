#pragma once

#include "EngineBase.h"
#include "Engine2DCollisionTypes.h"
#include "Engine2DIntegrationTypes.h"
#include <vector>

namespace phynet{
namespace phy{

struct Boundary2D
{
	math::Polygon2 m_poly;
	Real m_elasticity;
};

class ParticleEngine2D : public EngineBase
{
public:
	typedef std::vector<Boundary2D> Boundaries;
	typedef std::vector<ParticleContact2D> ParticleContacts;
	typedef math::Vector2 Vector2;

	void Init();
	
	//collision (maybe we'll move out the Collision Detection System)
	void EnableParticleCollisions(const bool i_enable = true);
	void EnableWorldCollisions(const bool i_enable = true);
	void EnableAllCollisions(const bool i_enable = true);
	bool IsParticleCollisionsEnabled() const;
	bool IsWorldCollisionsEnabled() const;
	bool IsAllCollisionsEnabled() const;

	const ParticleWorld2D& GetWorld() const;
	ParticleWorld2D& GetWorld();

	const Boundary2D& GetWorldBoundary() const;
	const Boundaries& GetInternalBoundaries() const;

	void SetWorldBoundary(const Boundary2D& i_boundary);
	void AddInternalBoundary(const Boundary2D& i_boundary);
	void ClearInternalBoundaries();

private:
	virtual void Step(const Real i_timeStep);

	void CalculateParticleContacts();
	void CalculateWorldContacts();
	void CalculateLinksContacts();
	void CheckBoundaryContact(const Boundary2D& i_boundary, Particle2D* i_particle, const bool i_isOuter);

	ParticleWorld2D m_world;

	//the static world can be supposed the internal of a big polygon
	Boundary2D m_staticWorldOutPoly;

	//there could be more "internal" static object that doesn't move.
	Boundaries m_staticWorldInPoly;

	bool m_particleCollisionsEnabled;
	bool m_worldCollisionsEnabled;

	ParticleContacts m_contacts;

};

}} // namespaces

#include "ParticleEngine2D.inl"


