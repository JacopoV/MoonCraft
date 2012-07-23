#ifndef SERVER_H
#define SERVER_H

#include "../../Common/Types.h"
#include "BitStream.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "RakNetTypes.h"
#include "../../Math/Vector2.h"
#include <iostream>
#include <string>
#include <map>
#include <SFML/System/Clock.hpp>

class PktManager;
class Game;

class Server
{
public:
	typedef RakNet::MessageID MessageID;
	typedef phynet::UInt UInt;
	typedef phynet::math::Vector2 Vector2;

	Server(void);
	~Server(void);

	bool Init();
	void Run();

	void AddClient(const RakNet::SystemAddress&);
	void RemoveClient(const RakNet::SystemAddress&);
	void RemoveAllClients();
	int GetPlayersNumber() const;
	RakNet::SystemAddress GetClientAddressAt(unsigned int) const;

private:
	static const int MAX_CLIENTS = 4;
	static const int SERVER_PORT = 60000;
	static const float MAX_SENDING_TIMER;
	void ManagePacket(RakNet::Packet*);
	RakNet::RakPeerInterface* mPeer;
	unsigned char mLastGameMessage;
	std::map<RakNet::SystemAddress, unsigned short> mClientsMap;
	bool mNewPlayerJoining;
	bool mClientDisconnected;
	Game* mGame;
	int mPlayersReady;
	sf::Clock mClock;
	void SendStartPacket(const RakNet::SystemAddress&);
	void SendGameState(const RakNet::SystemAddress&);
	void SendUpdateProjectiles(const RakNet::SystemAddress&);
	void SendUpdateClients(unsigned short int);
};

#include "Server.inl"

#endif
