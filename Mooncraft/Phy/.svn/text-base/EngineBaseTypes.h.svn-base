#pragma once

#include "common/types.h"

namespace phynet{
namespace phy{

struct EngineTimeParams
{
	Real m_timeStep; //milliscends of a simulation step
	Real m_timeElapsedSinceLastStep; //milliseconds "remaining" from last step
	Real m_slowMotionFactor; // 1.0f means normal behavior

	explicit EngineTimeParams(const Real i_timeStep = 1.0f/60.0f, const Real i_timeElapsedSinceLastStep = 0.0f, const Real i_slowMotionFactor = 1.0f)
		:m_timeStep(i_timeStep)
		,m_timeElapsedSinceLastStep(i_timeElapsedSinceLastStep)
		,m_slowMotionFactor(i_slowMotionFactor)
	{
	}
};

}} // namespaces
