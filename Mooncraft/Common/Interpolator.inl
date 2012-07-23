inline Interpolator::Interpolator(const Vector2& iStart, const Vector2& iTarget, const float iStep)
	:
	mStartPosition(iStart),
	mTargetPosition(iTarget),
	mStep(iStep),
	mCurrentStep(0.0f)
{}

inline void Interpolator::SetStep(const float iStep)
{
	mStep = iStep;
}

inline void Interpolator::SetData(const Vector2& iStart, const Vector2& iTarget, const float iStep)
{
	mCurrentStep = 0.0f;

	mStartPosition = iStart;
	mTargetPosition = iTarget;
	mStep = iStep;
}