#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <math.h>
#include "../Common/Types.h"
#include "../Math/Vector2.h"
#include "RakString.h"
#include <SFML/Graphics.hpp>

class Projectile;

class Player
{
public:
	typedef phynet::math::Vector2 Vector2;
	typedef phynet::UInt UInt;
	typedef RakNet::RakString RakString;
	
	Player(const RakString& iName, unsigned short iID, const Vector2& iPos, const Vector2& iDirection);
	void Init(const RakString& iName, unsigned short iID, const Vector2& iPosition, const Vector2& iDirection);
	~Player(void);
	static const float MAX_CANNON_DEGREE;
	static const float ROTATION_SPEED;
	static const UInt MAX_PROJECTILES = 5;
	static const UInt MAX_LIFE = 100;
	unsigned short GetID() const;
	RakString GetName() const;
	Vector2 GetPosition() const;
	Vector2 GetDirection() const;
	float GetCannonRotation() const;
	int GetProjectilesSize() const;
	UInt GetLife() const;
	UInt GetScore() const;

	void PlayerDestroyed(RakNet::RakString);
	RakNet::RakString GetPlayerDestroyed() const;
	void SetScore(UInt);
	void SetLife(UInt);
	void SetPosition(const Vector2&);
	void SetCannonRotation(float);
	Projectile* GetProjectileAt(int) const;
	void RemoveProjectileAt(int);
	void RemoveAllProjectiles();
	bool Shoot();
	void Shoot(Projectile*);
	void Remove();
	void Update(float);
	void Draw(sf::RenderWindow&,sf::Color&,float) const;
	void CheckCollisionWith(Player*);
	bool IsActive();
	void SetActive(bool);
	

private:
	static const float MAX_RELOAD_TIMER;
	unsigned short int mID;
	RakNet::RakString mName;
	RakNet::RakString mPlayerDestroyed;
	float mCannonRotation;
	float mMinRotation;
	float mMaxRotation;
	UInt mScore;
	UInt mLife;
	Vector2 mPosition;
	Vector2 mDirection;
	std::vector<Projectile*> mProjectiles;
	float mReloadTimer;
	bool mIsActive;
	
};

#include "Player.inl"
#endif