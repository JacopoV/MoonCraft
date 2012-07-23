#pragma once

#include "math/Polygon2.h"

#include "ParticleWorld.h"
#include "ParticleContact.h"
#include "ParticleRod.h"
#include "ParticleRope.h"

namespace phynet{
namespace phy{

typedef ParticleWorld<2> ParticleWorld2D;
typedef ParticleContact<2> ParticleContact2D;
typedef ParticleRod<2> ParticleRod2D;
typedef ParticleRope<2> ParticleRope2D;
typedef ParticleAnchoredRod<2> ParticleAnchoredRod2D;
typedef ParticleAnchoredRope<2> ParticleAnchoredRope2D;

}} // namespaces


