#pragma once

#include "Common/Types.h"

namespace phynet{
namespace phy{

class WorldBase
{
public:
	WorldBase(){}

	Real GetTime() const;

	virtual ~WorldBase(){};
	virtual void Update(const Real i_timeElapsed) = 0;

protected:
	Real m_currentTime;

private:
	WorldBase& operator=(const WorldBase&); //disabled
	WorldBase(const WorldBase&); //disabled
};

inline Real WorldBase::GetTime() const
{
	return m_currentTime;
}

}} // namespaces

