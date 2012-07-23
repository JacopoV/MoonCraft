#pragma once

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "../../Game/GameClient.h"
#include "../Math/Vector2.h"
#include <SFML/System/Clock.hpp>

class Player;

class Client
{
public:

	typedef phynet::math::Vector2 Vector2;
	typedef RakNet::SystemAddress SystemAddress;

	void Init();
	Client(void);
	~Client(void);

	unsigned char GetPacketIdentifier(RakNet::Packet *p);
	void SendPacket(unsigned char);
	void Run();
	void Disconnect();

private:

	sf::Clock mClock;
	int mPacketCounter;
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	char str[512];
	char mClientName[512];
	GameClient* mGame;
	SystemAddress mServerAddress;
	unsigned short int mID;
	bool mGameJoined;
	bool mGameStarted;
	void ManageInput(float);
	void ManagePacket(RakNet::Packet*);

};

