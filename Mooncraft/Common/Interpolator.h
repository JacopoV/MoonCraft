#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "../Math/Vector2.h"

class Interpolator
{
public:
	typedef phynet::math::Vector2 Vector2;
	Interpolator(const Vector2& iStart, const Vector2& iTarget, const float iStep);
	~Interpolator(void);

	Vector2 Interpolate(float iElapsed);
	void SetInterpolationTimer(const float);
	void SetStep(const float);
	void SetData(const Vector2& iStart, const Vector2& iTarget, const float iStep);


private:
	Vector2 mStartPosition;
	Vector2 mTargetPosition;
	float mCurrentStep;
	float mStep;
};

#include "Interpolator.inl"
#endif