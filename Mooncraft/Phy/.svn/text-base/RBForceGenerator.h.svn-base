#pragma once

#include "PhyMathUtils.h"

namespace phynet{
namespace phy{

template<int Dim>
class RBForceGenerator
{
public:
	typedef RigidBodyType<Dim>::Type RBType;
	typedef typename RigidBodyType<Dim>::VectorType VectorType;

	virtual ~ParticleForceGenerator(){}
	virtual void ApplyForce(RBType* i_rb) = 0;
};

}} // namespace phynet
