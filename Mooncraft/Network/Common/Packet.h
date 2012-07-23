#pragma once
#include "../../Common/Types.h"
#include "../../Network/Common/NetworkUtils.h"
#include "../../Math/Vector2.h"


namespace mooncraft
{

class Projectile;
class Player;
class Enemy;

struct ClientPacket
{
	typedef phynet::UInt UInt;

	UInt mPlayer;
	INPUT mInput;
};


struct ServerPacket
{

	std::vector<Player*> mPlayers;
	std::vector<Projectile*> mProjectiles;
	std::vector<Enemy*> mEnemies;

};

}//ns