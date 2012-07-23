#ifndef GAME_H
#define GAME_H

#include "../Math/Vector2.h"
#include "RakNetTypes.h"
#include <SFML/System/Clock.hpp>
#include <vector>

class Player;
class Projectile;
class Enemy;


class Game
{
public:
	typedef phynet::math::Vector2 Vector2;

	Game(void);
	~Game(void);
	bool Init();

	void ManagePacket(const RakNet::Packet*, RakNet::RakPeerInterface*, unsigned short);
	void Update(float);
	void Draw();
	void AddPlayer(Player*);
	void SetStarted(bool);
	bool IsStarted() const;
	Player* GetPlayerAt(int) const;
	Player* GetPlayerWithID(unsigned short) const;
	void RemovePlayerAt(int);
	int GetPlayersNumber() const;

protected:
	static const int MAX_BOUNDRY_X = 800;
	static const int MAX_BOUNDRY_Y = 600;
	sf::Clock mClock;
	std::vector<Player*> mPlayers;
	std::vector<Enemy*> mEnemies;
	bool IsTurningLeft[4];
	bool IsTurningRight[4];
	bool mIsStarted;
	void ManageCannonUpdate(const RakNet::Packet* iPacket, RakNet::RakPeerInterface* iPeer, unsigned short playerID, const char*);
	void ManageClientDisconnection(const RakNet::Packet* iPacket, RakNet::RakPeerInterface* iPeer);
	void CheckPlayerCollision();
	void CheckBoundryCollision();
	void CheckProjectileCollision();
	
	
};

#include "Game.inl"
#endif