#pragma once
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"


class RBWorldInterface;
class Server;

class PktManager
{
public:
	PktManager(Server*);
	~PktManager(void);

	void Manage(RakNet::Packet *packet, RakNet::RakPeerInterface *peer);
	const unsigned char GetLastGameMessage() const;

private:
	RBWorldInterface* m_worldInterface;
	unsigned char m_lastGameMessage;
	Server* mParent;
};