#include "ParticleEngine2D.h"
#include "Math/Geom2DUtils.h"

namespace phynet{
namespace phy{

void ParticleEngine2D::Init()
{
	m_world.Init();

	m_staticWorldInPoly.clear();
	m_staticWorldOutPoly.m_poly = math::Polygon2();
	m_staticWorldOutPoly.m_elasticity = 0.0f;
	m_contacts.clear();

	m_particleCollisionsEnabled = false;
	m_worldCollisionsEnabled = false;
}

void ParticleEngine2D::Step(const Real i_timeStep)
{
	m_world.Update(i_timeStep);

	//simple particle collision detection
	int maxCycles = 2;
	bool isFinished = false;
	while(!isFinished)
	{
		m_contacts.clear();
		//collision detection
		CalculateParticleContacts();
		CalculateWorldContacts();
		CalculateLinksContacts();
		
		//collision resolution
		for(size_t j=0; j<m_contacts.size(); ++j)
			m_contacts[j].Resolve(i_timeStep);

		isFinished = m_contacts.empty() || (--maxCycles == 0);
	}
}

void ParticleEngine2D::CalculateParticleContacts()
{
	if(!m_particleCollisionsEnabled)
		return;

	const ParticleWorld2D::Particles& particles = m_world.GetParticles();
	for(size_t i=0; i<particles.size(); ++i)
	{
		for(size_t j=i+1; j<particles.size(); ++j)
		{
			Vector2 normal = particles[i]->GetPosition() - particles[j]->GetPosition();
			const Real radiusSum = particles[i]->GetRadius() + particles[j]->GetRadius();
			const Real squarePenetration = radiusSum * radiusSum - normal.SquareMagnitude();
			if(math::GreaterThan(squarePenetration, 0.0f))
			{
				m_contacts.push_back(ParticleContact2D(
					particles[i], 
					particles[j], 
					normal.Normalize(), 
					sqrt(squarePenetration), 
					particles[i]->GetElasticity() * particles[j]->GetElasticity() ));
			}
		}
	}
}

void ParticleEngine2D::CheckBoundaryContact(const Boundary2D& i_boundary, Particle2D* i_particle, const bool i_isOuter)
{
	const math::Polygon2::Points& points = i_boundary.m_poly.GetPoints();
	const size_t numPoints = points.size();
	
	bool outside = false;
	if(i_isOuter != i_boundary.m_poly.IsInside(i_particle->GetPosition()))
		outside = true;

	bool outsideResolved = !outside;
	Real minDistance = 0.0f;
	int minDistanceIndex = -1;
	for(size_t i=0; i< numPoints; ++i)
	{
		const Real dist = math::DistancePointSegment(points[i], points[(i+1)%numPoints], i_particle->GetPosition());
		if(dist < i_particle->GetRadius())
		{
			outsideResolved = true;
			Vector2 AB = points[(i+1)%numPoints] - points[i];
			Vector2 normal(-AB.Y(), AB.X());
			m_contacts.push_back(
				ParticleContact2D(
					i_particle, 
					0, 
					i_isOuter ? normal.Normalize() : -normal.Normalize(),
					outside ? i_particle->GetRadius() + dist : i_particle->GetRadius() - dist, 
					i_particle->GetElasticity()*i_boundary.m_elasticity));
		}
		else
		{
			if((minDistanceIndex == -1))
			{
				minDistanceIndex = i;
				minDistance = dist;
			}
			else
			{
				if(dist < minDistance)
				{
					minDistance = dist;
					minDistanceIndex = i;
				}
			}
		}
	}

	if(!outsideResolved)
	{
		Vector2 AB = points[(minDistanceIndex+1)%numPoints] - points[minDistanceIndex];
		Vector2 normal(-AB.Y(), AB.X());
		m_contacts.push_back(
			ParticleContact2D(
				i_particle, 
				0, 
				i_isOuter ? normal.Normalize() : -normal.Normalize(),
				outside ? i_particle->GetRadius() + minDistance : i_particle->GetRadius() - minDistance, 
				i_particle->GetElasticity()*i_boundary.m_elasticity));
	}
}

void ParticleEngine2D::CalculateWorldContacts()
{
	if(!m_worldCollisionsEnabled)
		return;
	
	// outer polygon
	if(m_staticWorldOutPoly.m_poly.GetPoints().size() > 2)
	{
		const Particles2D& theParticles = m_world.GetParticles();
		for(size_t i = 0; i < theParticles.size(); ++i)
			CheckBoundaryContact(m_staticWorldOutPoly, theParticles[i], true);
	}

	// inner polygons
	for (size_t j = 0; j < m_staticWorldInPoly.size(); ++j)
	{
		const Particles2D& theParticles = m_world.GetParticles();
		for(size_t i = 0; i < theParticles.size(); ++i)
			CheckBoundaryContact(m_staticWorldInPoly[j], theParticles[i], false);
	}
}

void ParticleEngine2D::CalculateLinksContacts()
{
	ParticleContact2D thecontact;
	const ParticleWorld2D::Links& links = m_world.GetLinks();
	for(UInt i=0; i<links.size(); ++i)
	{
		const int num = links[i]->AddContact(&thecontact);
		if(num>0)
			m_contacts.push_back(thecontact);
	}
}

}} // namespaces
