#pragma once
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"

class RBWorldInterface;

class PktManager
{
public:
	PktManager(void);
	~PktManager(void);

	void Init();
	void Manage(RakNet::Packet *packet, RakNet::RakPeerInterface *peer);

	const unsigned char GetLastGameMessage() const;

private:
	RBWorldInterface* m_worldInterface;
	unsigned char m_lastGameMessage;
};