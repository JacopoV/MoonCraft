#pragma once


#include "math/Vector2.h"
#include "math/Polygon2.h"
#include "math/Circle2.h"
#include "Phy/PhyMathUtils.h"

namespace phynet{
namespace phy{

class RigidBody2D
{
public:
	typedef math::Vector2 Vector2;
	typedef math::Polygon2 Polygon2;
	typedef math::Circle2 Circle2;
	
	RigidBody2D(){}

	RigidBody2D(const Real i_mass, 
		const Real i_inertiaTensor,
		const Real i_linearDamping, 
		const Real i_angularDamping, 
		const Real i_elasticity, 
		const Vector2& i_pos, 
		const Vector2& i_linearVel,
		const Vector2& i_orientation,
		const Real i_angularVelocity,
		const Polygon2& i_shape,
		const Circle2& i_bs = INVALID_BS());
	
	void Init(const Real i_mass, 
		const Real i_inertiaTensor,
		const Real i_linearDamping, 
		const Real i_angularDamping, 
		const Real i_elasticity, 
		const Vector2& i_pos, 
		const Vector2& i_linearVel,
		const Vector2& i_orientation,
		const Real i_angularVelocity,
		const Polygon2& i_shape,
		const Circle2& i_bs = INVALID_BS());

	const Vector2& GetPosition() const {return m_position;}
	const Vector2& GetLinearVelocity() const {return m_linearVelocity;}
	const Vector2& GetLinearAcceleration() const {return m_linearAcceleration;}
	const Real GetLinearDamping() const {return m_linearDamping;}

	void SetPosition(const Vector2& i_pos) {m_position = i_pos;}
	void SetLinearVelocity(const Vector2& i_linVel) {m_linearVelocity = i_linVel;}
	void SetLinearAcceleration(const Vector2& i_linAcc) {m_linearAcceleration = i_linAcc;}
	void SetLinearDamping(const Real i_linDamp) {m_linearDamping = i_linDamp;}
	

	const Vector2& GetOrientation() const {return m_orientation;}
	const Real GetAngularVelocity() const {return m_angularVelocity;}
	const Real GetAngularAcceleration() const {return m_angularAcceleration;}
	const Real GetAngularDamping() const {return m_angularDamping;}

	void SetOrientation(const Vector2& i_orien) {m_orientation = i_orien;}
	void SetAngularVelocity(const Real i_angVel) {m_angularVelocity = i_angVel;}
	void SetAngularAcceleration(const Real i_angAcc) {m_angularAcceleration = i_angAcc;}
	void SetAngularDamping(const Real i_angDamp) {m_angularDamping = i_angDamp;}

	const Real GetMass() const {return m_mass;}
	const Real GetInverseMass() const {return m_inverseMass;}
	const Real GetInertiaTensor() const {return m_inertiaTensor;}
	const Real GetInverseInertiaTensor() const {return m_inverseInertiaTensor;}

	void SetMass(const Real i_mass) 
	{
		m_mass = i_mass;
		m_inverseMass = math::AreEqual(i_mass, 0.0f) ? 0.0f : (1.0f/i_mass);
	}
	
	void SetInertiaTensor(const Real i_it)
	{
		m_inertiaTensor = i_it;
		m_inverseInertiaTensor = math::AreEqual(i_it, 0.0f) ? 0.0f : (1.0f/i_it);
	}

	// collision
	const Real GetElasticity() const {return m_elasticity;}

	const Polygon2& GetShape() const {return m_shape;}
	const Circle2& GetBoundingSphere() const {return m_bs;}

	const Polygon2 GetShapeWorldCoordinate() const;
	const Circle2 GetBoundingSphereWorldCoordinate() const;

	void SetElasticity(const Real i_elasticity) {m_elasticity = i_elasticity;}
	void SetShape(const Polygon2& i_shapeInLocalCoordinate) {m_shape = i_shapeInLocalCoordinate;}
	void SetBoundingSphere(const Circle2& i_bsInLocalCoord) {m_bs = i_bsInLocalCoord;}

	void AddForce(const Vector2& i_force);
	void AddTorque(const Real i_torque);
	void AddForceAtPoint(const Vector2& i_force, const Vector2& i_pointInWorldCoordinate);

	void AddLinearImpulse(const Vector2& i_impulse);
	void AddAngularImpulse(const Real i_impulse);

	void Integrate(const Real i_elapsedTime);

	//mine 
	void GetParallelAxis(Vector2 o_axis1, Vector2 o_axis2);

	//movement
	void Move(const Vector2& i_move);
	

private:
	//Linear cinematic
	Vector2 m_position;
	Vector2 m_linearVelocity;
	Vector2 m_linearAcceleration;
	Real m_linearDamping;

	//Angular cinematic
	Vector2 m_orientation; //spinor = complex number
	Real m_angularVelocity;
	Real m_angularAcceleration;
	Real m_angularDamping;

	//dynamic
	Vector2 m_totalForce;
	Real m_totalTorque;

	Real m_mass;
	Real m_inverseMass;

	Real m_inertiaTensor;
	Real m_inverseInertiaTensor;

	// collision
	Real m_elasticity;
	Polygon2 m_shape;
	Circle2 m_bs;
};

}} // namespaces

#include "RigidBody2d.inl"

