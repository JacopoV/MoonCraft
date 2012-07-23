#pragma once
#include "PktManager.h"
#include "NetworkUtils.h"
#include "GetTime.h"
#include "RakNetTypes.h"  // MessageID
#include "BitStream.h"
#include "../../Phy/RBWorldInterface.h"
#include "../Server/Server.h"
#include <iostream>

PktManager::PktManager(Server* iParent)
{
	mParent = iParent;
}

PktManager::~PktManager(void)
{
	if(m_worldInterface)
		delete m_worldInterface;
}

void PktManager::Manage(RakNet::Packet *packet, RakNet::RakPeerInterface *peer)
{
	m_lastGameMessage = GetPacketIdentifier(packet);
	switch (m_lastGameMessage)
	{
	case ID_REMOTE_DISCONNECTION_NOTIFICATION:
		printf("Another client has disconnected.\n");
		break;
	case ID_REMOTE_CONNECTION_LOST:
		printf("Another client has lost the connection.\n");
		break;
	case ID_REMOTE_NEW_INCOMING_CONNECTION:
		printf("Another client has connected.\n");
		mParent->AddClient(packet->systemAddress);
		break;	
	case ID_NEW_INCOMING_CONNECTION:
		printf("A connection is incoming.\n");
		mParent->AddClient(packet->systemAddress);
		break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
		printf("The server is full.\n");
		break;
	case ID_DISCONNECTION_NOTIFICATION:
		printf("A client has disconnected.\n");
		mParent->RemoveClient(packet->systemAddress);
		break;
	case ID_CONNECTION_LOST:
		printf("A client lost the connection.\n");
		mParent->RemoveClient(packet->systemAddress);
		break;
	case ID_GAME_MESSAGE_1:
		{
			RakNet::RakString rs;
			//RakNet::Time timeStamp;

			RakNet::BitStream bsIn(packet->data,packet->length,false);

			////Reading the timestamp
			//bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			//bsIn.Read(timeStamp);
			//printf("Messaggio inviato halle %i\n: ", timeStamp);

			//Reading the string
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(rs);
			printf("%s\n", rs.C_String());

		}
		break;
	case ID_CLIENT_WANNA_PLAY:

		if(1)//tutti vogliono giocare
		{

			char positions []= {'n', 's', 'e', 'o'};
			for(int i=0; i<mParent->GetPlayersNumber(); ++i)
			{
				printf("Sending ID_START_NEW_GAME to: %s \n", mParent->GetClientAddressAt(i).ToString());
				RakNet::BitStream bsOut;
				bsOut.Write((RakNet::MessageID)ID_START_NEW_GAME);
				bsOut.Write(mParent->GetPlayersNumber());
				bsOut.Write(positions[i]);
				//There are playersNumber-1 other players
				int index;
				for(int j=1; j<mParent->GetPlayersNumber(); ++j)
				{
					index = i+j;
					if(index > 3)
						index = 0;
					bsOut.Write(positions[index]);
				}
				
				peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,mParent->GetClientAddressAt(i),false);
			}
		}

		break;
	default:
		printf("Message with identifier %i has arrived.\n", packet->data[0]);
		break;
	}
}

const unsigned char PktManager::GetLastGameMessage() const
{
	return m_lastGameMessage;
}