#pragma once

#include "EngineBaseTypes.h"

namespace phynet{
namespace phy{

class EngineBase
{
public:
	EngineBase(){}
	virtual ~EngineBase(){};

	const EngineTimeParams& GetTimeParams() const;
	void SetTimeParams(const EngineTimeParams& i_timeParams);
	
	void Update(const Real i_timeElapsedMilliSec);

protected:
	virtual void Step(const Real i_timeStep) = 0;

private:
	EngineTimeParams m_timeParams;
};

inline const EngineTimeParams& EngineBase::GetTimeParams() const
{
	return m_timeParams;
}

inline void EngineBase::SetTimeParams(const EngineTimeParams& i_timeParams)
{
	m_timeParams = i_timeParams;
}

inline void EngineBase::Update(const Real i_timeElapsedMilliSec)
{
	m_timeParams.m_timeElapsedSinceLastStep += i_timeElapsedMilliSec * m_timeParams.m_slowMotionFactor;
	while(m_timeParams.m_timeElapsedSinceLastStep > m_timeParams.m_timeStep)
	{
		Step(m_timeParams.m_timeStep);
		m_timeParams.m_timeElapsedSinceLastStep -= m_timeParams.m_timeStep;
	}
}

}} // namespaces

