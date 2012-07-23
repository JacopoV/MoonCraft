namespace phynet{
namespace phy{

inline RigidBody2D::RigidBody2D(const Real i_mass, 
	const Real i_inertiaTensor,
	const Real i_linearDamping, 
	const Real i_angularDamping, 
	const Real i_elasticity, 
	const Vector2& i_pos, 
	const Vector2& i_linearVel,
	const Vector2& i_orientation,
	const Real i_angularVelocity,
	const Polygon2& i_shape,
	const Circle2& i_bs)
{
	Init(i_mass,
		i_inertiaTensor,
		i_linearDamping, 
		i_angularDamping, 
		i_elasticity, 
		i_pos, 
		i_linearVel,
		i_orientation,
		i_angularVelocity,
		i_shape,
		i_bs);
}
	
inline void RigidBody2D::Init(const Real i_mass, 
	const Real i_inertiaTensor,
	const Real i_linearDamping, 
	const Real i_angularDamping, 
	const Real i_elasticity, 
	const Vector2& i_pos, 
	const Vector2& i_linearVel,
	const Vector2& i_orientation,
	const Real i_angularVelocity,
	const Polygon2& i_shape,
	const Circle2& i_bs)
{
	SetMass(i_mass);
	SetInertiaTensor(i_inertiaTensor);
	SetLinearDamping(i_linearDamping);
	SetAngularDamping(i_angularDamping);
	SetElasticity(i_elasticity);
	SetPosition(i_pos);
	SetLinearVelocity(i_linearVel);
	SetOrientation(i_orientation);
	SetAngularVelocity(i_angularVelocity);
	SetShape(i_shape);
	SetBoundingSphere(i_bs);
}

inline const math::Polygon2 RigidBody2D::GetShapeWorldCoordinate() const 
{
	//TODO
	return m_shape; // wrong wrong!!!
}

inline const math::Circle2 RigidBody2D::GetBoundingSphereWorldCoordinate() const 
{
	//to be optimized
	return Circle2(m_position, m_bs.GetRadius());
}

inline void RigidBody2D::GetParallelAxis(Vector2 o_axis1, Vector2 o_axis2)
{

	//Se mOrientation è vettore orientazione rigidbody:
	m_orientation.Normalize();
	if(m_orientation.X() == 0)
	{
		o_axis1 = m_orientation;
		o_axis2.Set(0, 1);
		return;
	}

	if(m_orientation.Y() == 0)
	{
		o_axis1.Set(1, 0);
		o_axis2 = m_orientation;
		return;
	}

	o_axis1 = m_shape.GetPoints().at(0) - m_shape.GetPoints().at(1);
	o_axis2 = m_shape.GetPoints().at(1) - m_shape.GetPoints().at(2);

	o_axis1.Normalize();
	o_axis2.Normalize();
	
	return;
}


}} // namespaces



