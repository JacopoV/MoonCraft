//////////////////////////////////
//   Projectile.inl
/////////////////////////////////

inline Projectile::Projectile(const Vector2& iPos, const Vector2& iDirection, unsigned short int iParent)
	:
	mPos(iPos), 
	mDirection(iDirection), 
	mParent(iParent), 
	mSpeed(50),
	mRadius(10),
	mLife(1),
	mInterpolator(new Interpolator(iPos, iPos, 1.0f))

{
}

inline unsigned short int Projectile::GetParent() const 
{
	return mParent;
}

inline Projectile::Vector2 Projectile::GetPos() const
{
	return mPos;
}

inline Projectile::Vector2 Projectile::GetDirection() const
{
	return mDirection;
}

inline int Projectile::GetLife() const
{
	return mLife;
}

inline float Projectile::GetSpeed() const
{
	return mSpeed;
}


inline void Projectile::SetDirection(const Vector2& iDirection)
{
	mDirection = iDirection;
}

inline void Projectile::SetPosition(const Vector2& iPosition)
{
	mPos = iPosition;
}

inline void Projectile::SetLife(int iLife)
{
	mLife = iLife;
}

inline float Projectile::GetRadius() const
{
	return mRadius;
}

inline Interpolator* Projectile::GetInterpolator() const
{
	return mInterpolator;
}

