#include "Interpolator.h"
#include "../Network/Common/NetworkUtils.h"

Interpolator::Vector2 Interpolator::Interpolate(float iElapsed)
{
	mCurrentStep += mStep * iElapsed;
	return lerpVector(mStartPosition, mTargetPosition, mCurrentStep);
}