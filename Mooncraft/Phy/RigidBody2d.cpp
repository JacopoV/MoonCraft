#include "RigidBody2d.h"
#include <cmath>

namespace phynet{
namespace phy{

void RigidBody2D::AddForce(const Vector2& i_force)
{
	m_totalForce += i_force;
}

void RigidBody2D::AddTorque(const Real i_torque)
{
	m_totalTorque += i_torque;
}

void RigidBody2D::AddForceAtPoint(const Vector2& i_force, const Vector2& i_pointInWorldCoordinate)
{
	AddForce(i_force);

	const Vector2 cp = m_position - i_pointInWorldCoordinate;
	const Real torque = cp.X() * i_force.Y() - cp.Y() * i_force.X();
	AddTorque(torque);
}

void RigidBody2D::AddLinearImpulse(const Vector2& i_impulse)
{
	//TODO //CHECK CHECKCHECK CHECKCHECK CHECKCHECK CHECKCHECK CHECKCHECK CHECK
	m_linearVelocity += i_impulse * GetInverseMass();
}

void RigidBody2D::AddAngularImpulse(const Real i_impulse)
{
	//TODO
}

void RigidBody2D::Integrate(const Real i_elapsedTime)
{
	//linear integration
	m_linearAcceleration = m_totalForce * m_inverseMass;
	m_position += m_linearVelocity * i_elapsedTime; // m_acceleration * i_elapsedTime * i_elapsedTime * 0.5f
	m_linearVelocity = m_linearDamping * m_linearVelocity + m_linearAcceleration * i_elapsedTime;

	//angular integration
	m_angularAcceleration = m_totalTorque * m_inverseInertiaTensor;
	const Real deltaTheta = m_angularVelocity * i_elapsedTime;
	Vector2 deltaOrientation(std::cos(deltaTheta), std::sin(deltaTheta));
	m_orientation = SpinorProduct(m_orientation, deltaOrientation);
	m_angularVelocity = m_angularDamping * m_angularVelocity + m_angularAcceleration * i_elapsedTime;

	// clear forces
	m_totalForce.Zero();
	m_totalTorque = 0.0f;
}

void RigidBody2D::Move(const Vector2& i_move){

	Vector2 fst = m_shape.GetPoints().at(0);
	Vector2 snd = m_shape.GetPoints().at(1);
	Vector2 thr = m_shape.GetPoints().at(2);
	Vector2 frt = m_shape.GetPoints().at(3);

    phynet::math::Polygon2::Points points;
		points.push_back(Vector2(fst.X()+i_move.X(), fst.Y()+i_move.Y()));
		points.push_back(Vector2(snd.X()+i_move.X(), snd.Y()+i_move.Y()));
		points.push_back(Vector2(thr.X()+i_move.X(), thr.Y()+i_move.Y()));
		points.push_back(Vector2(frt.X()+i_move.X(), frt.Y()+i_move.Y())); 

	m_shape.SetPoints(points);

}


}} // namespaces

