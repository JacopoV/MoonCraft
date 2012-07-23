#pragma once
#include "Phy\WorldBase.h"
#include "Math\Vector2.h"

namespace phynet{
namespace phy{

class RigidBody2D;

class RigidBodyWorld: public WorldBase
{
public:
	typedef std::vector<RigidBody2D*> RigidBodies;
	typedef std::vector<phynet::math::Vector2> Forces;

	RigidBodyWorld(void);
	~RigidBodyWorld(void);

	void Init();
	void Clear();
	
	//particle management
	const RigidBodies& GetRigidBodies() const;
	void AddRigidBodyUnchecked(RigidBody2D* const i_rigidBody);
	void AddRigidBody(RigidBody2D* const i_rigidBody);
	void AddRigidBody(RigidBody2D* const i_rigidBody, const int i_numRigidBodies, const bool i_checked = false);
	void AddRigidBodies(RigidBody2D** const i_rigidBody, const int i_numRigidBodies, const bool i_checked = false);
	void RemoveRigidBody(RigidBody2D* const i_rigidBody);
	void RemoveRigidBodies(RigidBody2D* const i_rigidBody, const int i_numRigidBodies);
	void RemoveRigidBodies(RigidBody2D** const i_rigidBody, const int i_numRigidBodies);
	void RemoveRigidBody(const UInt i_Index);
	void RemoveAllRigidBodies();

	//force management
	//const Forces& GetForces() const;
	//void AddForce(ForceType* const i_force);
	//void RemoveForce(ForceType* const i_force);
	//void RemoveAllForces();

	//force/particle pairing
	void AddForceOnRigidBody(const phynet::math::Vector2& i_force, const RigidBody2D& i_rigidBody);
	//void AddForceOnParticles(const phynet::math::Vector2& i_force, ParticleType* const i_particles, const int i_numParticles);
	void AddForceOnRigidBodies(const phynet::math::Vector2& i_force, RigidBody2D** const i_rigidBodies, const int i_numRigidBodies);
	void RemoveForceOnRigidBody(const phynet::math::Vector2& i_force, RigidBody2D* const i_rigidBody);
	void RemoveAllForcesOnRigidBodies();

	////links
	//const Links& GetLinks() const;
	//void AddLink(LinkType* const i_link);
	//void RemoveLink(LinkType* const i_link);
	//void RemoveAllLinks();
	
	virtual void Update(const Real i_timeelapsed);

private:
	RigidBodies m_rigidBodies;
	Forces m_forces;
	//RegistryType m_registry;

	//Links m_links;
};

}}

