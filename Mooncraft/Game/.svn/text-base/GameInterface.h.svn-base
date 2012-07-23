#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <vector>

namespace Mooncraft
{


class GameInterface
{
public:
	void Pos();
	void DispatchPkt(RakNet::Packet*);

private:
	std::vector<Player*> mPlayers;
	std::vector<Projectile*> mProjectiles;
	std::vector<Enemy*> mEnemies;
	
};

}//ns

#endif