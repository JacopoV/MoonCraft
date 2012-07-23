#include "../Network/Common/NetworkUtils.h"

inline Player::Player(const RakString& iName, unsigned short iID, const Vector2& iPosition, const Vector2& iDirection) 
	:
	mName(iName),
	mPlayerDestroyed("NONE"),
	mID(iID), 
	mPosition(iPosition),
	mDirection(iDirection),
	mScore(0), 
	mLife(MAX_LIFE),
	mReloadTimer(0),
	mIsActive(true)
{

		// Get from direction the cannon rotation
	// Player with rotation 0:
	//
	//              |
	//              v
	float cosAlfa = Dot(Vector2(0,1), iDirection);
	mCannonRotation = RadiansToDegree(std::acos(cosAlfa));
	if(iDirection.X() < 0)
		mCannonRotation*=-1;

	switch(mID)
	{
	case 0:
		//Player with default direction:
		//		|
		//		v
		//      0°
		//Limits: +90 - 90
		mMinRotation = - 80.0f;
		mMaxRotation = 80.0f;
		break;
	case 1:
		//Player with default direction <-
		//Limits: -10 - 170
		mMinRotation = -170.0f;
		mMaxRotation = -10.0f;
		break;
	case 2:
		mMinRotation = 100.0f;
		mMaxRotation = 260.0f;
		break;
	case 3:
		mMinRotation = 10.0f;
		mMaxRotation = 170.0f;
		break;
	}


}

inline void Player::Init(const RakString& iName, unsigned short iID, const Vector2& iPosition, const Vector2& iDirection)
{
	mName = iName;
	mPlayerDestroyed = "NONE";
	mID = iID;
	mPosition = iPosition;
	mDirection = iDirection;	
	mScore = 0;
	mLife = MAX_LIFE;
	mReloadTimer = 0;
	mIsActive = true;

	// Get from direction the cannon rotation
	// Player with rotation 0:
	//
	//              |
	//              v
	float cosAlfa = Dot(Vector2(0,1), iDirection);
	mCannonRotation = RadiansToDegree(std::acos(cosAlfa));
	if(iDirection.X() < 0)
		mCannonRotation*=-1;

	switch(mID)
	{
	case 0:
		//Player with default direction:
		//		|
		//		v
		//      0°
		//Limits: +90 - 90
		mMinRotation = - 80.0f;
		mMaxRotation = 80.0f;
		break;
	case 1:
		//Player with default direction <-
		//Limits: -10 - 170
		mMinRotation = -170.0f;
		mMaxRotation = -10.0f;
		break;
	case 2:
		mMinRotation = 100.0f;
		mMaxRotation = 260.0f;
		break;
	case 3:
		mMinRotation = 10.0f;
		mMaxRotation = 170.0f;
		break;
	}
}

inline Player::~Player()
{
	//TODo
}

inline RakNet::RakString Player::GetName() const
{
	return mName;
}

inline unsigned short Player::GetID() const
{
	return mID;
}

inline Player::Vector2 Player::GetPosition() const 
{ 
	return mPosition; 
}

inline Player::Vector2 Player::GetDirection() const 
{ 
	return mDirection;
}

inline float Player::GetCannonRotation() const
{
	return mCannonRotation;
}

inline void Player::PlayerDestroyed(RakNet::RakString iName)
{
	mPlayerDestroyed = iName;	
}

inline RakNet::RakString Player::GetPlayerDestroyed() const
{
	return mPlayerDestroyed;
}

inline void Player::SetScore(Player::UInt iValue)
{
	mScore = iValue;
}


inline void Player::SetLife(Player::UInt iValue)
{
	mLife = iValue;
}

inline void Player::SetPosition(const Vector2& iPosition)
{
	mPosition = iPosition;
}

inline void Player::SetCannonRotation(float iRotation)
{
	//if(iRotation > MAX_CANNON_DEGREE)
	//	mCannonRotation = MAX_CANNON_DEGREE;

	//if(iRotation < -MAX_CANNON_DEGREE)
	//	mCannonRotation = -MAX_CANNON_DEGREE;
	mCannonRotation = iRotation;

	if(iRotation > mMaxRotation)
		mCannonRotation = mMaxRotation;

	if(iRotation < mMinRotation)
		mCannonRotation = mMinRotation;

	mDirection.X() = sin(DegreeToRadians(iRotation /*- mID * 90*/));
	mDirection.Y() = cos(DegreeToRadians(iRotation /*- mID * 90*/));
}

inline Projectile* Player::GetProjectileAt(int i) const
{
	return mProjectiles[i];
}

inline int Player::GetProjectilesSize() const
{
	return mProjectiles.size();
}

inline Player::UInt Player::GetLife() const
{
	return mLife;
}

inline Player::UInt Player::GetScore() const
{
	return mScore;
}

inline void Player::Shoot(Projectile* iProjectile)
{
	mProjectiles.push_back(iProjectile);
}

inline void Player::Remove()
{
	mProjectiles.pop_back();
}

inline void Player::RemoveAllProjectiles()
{
	mProjectiles.clear();
}

inline bool Player::IsActive()
{
	return mIsActive;
}

inline void Player::SetActive(bool iActive)
{
	mIsActive = iActive;
}
