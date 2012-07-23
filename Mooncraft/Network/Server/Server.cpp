#include "Server.h"
#include "../Common/NetworkUtils.h"
#include "../Common/PktManager.h"
#include "../../Game/Game.h"
#include "../../Game/Player.h"
#include "../../Game/Projectile.h"
#include "RakSleep.h"
#include "GetTime.h"


const float Server::MAX_SENDING_TIMER = 0.0f;

Server::Server(void)
	:
mPlayersReady(0),
	mNewPlayerJoining(false),
	mClientDisconnected(false)
{
	if(!Init())
		exit(EXIT_FAILURE);

	if(!mGame->Init())
		exit(EXIT_FAILURE);
}


Server::~Server(void)
{
	if(mPeer)
		RakNet::RakPeerInterface::DestroyInstance(mPeer);
}

bool Server::Init()
{
	mPeer = RakNet::RakPeerInterface::GetInstance();

	printf("Starting the server. Max clients: %i Server port: %i \n", MAX_CLIENTS, SERVER_PORT);
	mPeer->Startup(MAX_CLIENTS, &RakNet::SocketDescriptor(SERVER_PORT,0), 1);

	printf("Set maximum connections %i \n", MAX_CLIENTS);
	mPeer->SetMaximumIncomingConnections(MAX_CLIENTS);

	mGame = new Game();
	mClock = sf::Clock();

	return true;
}

void Server::Run()
{
	RakNet::Packet *packet;
	while (mLastGameMessage != static_cast<unsigned int>(ID_GAME_OVER))//!!!!!!!!!!!todo!!!!
	{
		float elapsedTime = mClock.GetElapsedTime();
		mClock.Reset();

		for (packet=mPeer->Receive(); packet; mPeer->DeallocatePacket(packet), packet=mPeer->Receive())
		{
			ManagePacket(packet);
			if(!mNewPlayerJoining)
			{
				std::map<RakNet::SystemAddress, unsigned short>::const_iterator it = mClientsMap.find(packet->systemAddress);
				if(it._Ptr != NULL)
				{
					mGame->ManagePacket(packet, mPeer, it->second);
				}
			}
				
		}

		if(!mNewPlayerJoining)
		{
			mGame->Update(elapsedTime);
			//ManageDisconnectionClientsMap();
			for(std::map<RakNet::SystemAddress, unsigned short>::const_iterator it = mClientsMap.begin(); it != mClientsMap.end(); ++it)
			{

				SendGameState(it->first);
				SendUpdateProjectiles(it->first);
			}
		}
		
		RakSleep(25);
	}
}

void Server::ManagePacket(RakNet::Packet *packet)
{
	mLastGameMessage = GetPacketIdentifier(packet);
	switch (mLastGameMessage)
	{
	case ID_REMOTE_DISCONNECTION_NOTIFICATION:
		printf("Another client has disconnected.\n");
		RemoveClient(packet->systemAddress);
		break;
	case ID_REMOTE_CONNECTION_LOST:
		printf("Another client has lost the connection.\n");
		RemoveClient(packet->systemAddress);
		break;
	case ID_REMOTE_NEW_INCOMING_CONNECTION:
		printf("Another client has connected.\n");
		//mNewPlayerJoining = true;
		//AddClient(packet->systemAddress);
		break;	
	case ID_NEW_INCOMING_CONNECTION:
		printf("A connection is incoming.\n");
		mNewPlayerJoining = true;
		AddClient(packet->systemAddress);
		break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
		printf("The server is full.\n");
		break;
	case ID_DISCONNECTION_NOTIFICATION:
		printf("A client has disconnected.\n");
		RemoveClient(packet->systemAddress);
		break;
	case ID_CONNECTION_LOST:
		printf("A client lost the connection.\n");
		RemoveClient(packet->systemAddress);
		break;
	case ID_GAME_MESSAGE_1:
		{
			RakNet::BitStream bsIn(packet->data,packet->length,false);

			RakNet::RakString rs;
			RakNet::Time timeStamp;
			//Reading the timestamp
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(timeStamp);
			printf("Messaggio inviato alle %i \n: ", timeStamp);

			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(rs);//nome del player

			Vector2 direction(0,0);
			switch(mClientsMap[packet->systemAddress])
			{
			case 0:
				direction.Set(0, 1);
				break;
			case 1:
				direction.Set(-1, 0);
				break;
			case 2:
				direction.Set(0, -1);
				break;
			case 3:
				direction.Set(1, 0);
				break;
			}
			mGame->AddPlayer(new Player(rs, mClientsMap[packet->systemAddress], Player::Vector2(0,0),direction));
			printf("%s I am client with ID %u and SystemAddress %s \n", rs.C_String(), mClientsMap[packet->systemAddress], packet->systemAddress.ToString());

			unsigned short ID = mClientsMap[packet->systemAddress];

			//////////////////////////////////
			// Use timestamp
			/////////////////////////////////
			timeStamp = RakNet::GetTime();
			RakNet::BitStream bsOut;
			bsOut.Write((MessageID)ID_TIMESTAMP);
			bsOut.Write(timeStamp);
			bsOut.Write((RakNet::MessageID)ID_RETRIEVE);
			bsOut.Write(ID);
			mPeer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

		}
		break;
	case ID_CLIENT_WANNA_PLAY:
		{
			RakNet::BitStream bsIn(packet->data,packet->length,false);
			bsIn.IgnoreBytes(sizeof(MessageID));
			Vector2 position;
			bsIn.Read(position.X());
			bsIn.Read(position.Y());

			mGame->GetPlayerWithID(mClientsMap[packet->systemAddress])->SetPosition(position);
			mPlayersReady+=1;

			if(mGame->IsStarted())
			{
				/////////////////////////////////////////////////////////////////////////////////////////
				//If the game is already started, it means a player wants to join the current game
				/////////////////////////////////////////////////////////////////////////////////////////
				mNewPlayerJoining = true;

				///////////////////////////////////////////////////////////
				//  Send him the entire state
				///////////////////////////////////////////////////////////
				printf("Sending ID_START_NEW_GAME to THE NEW PLAYER \n");
				RakNet::BitStream bsOut;
				bsOut.Write((MessageID)ID_START_NEW_GAME);
				bsOut.Write(mClientsMap.size());//Tot players

				for(UInt j=0; j<mClientsMap.size(); ++j)
				{
					bsOut.Write(mGame->GetPlayerAt(j)->GetID());//ID
					bsOut.Write(mGame->GetPlayerAt(j)->GetName());//Send others players' name
				}
				mPeer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

				///////////////////////////////////////////////////////////
				//Send the already playing users the new player's info
				///////////////////////////////////////////////////////////
				printf("Sending ID_PLAYER_JOINED_GAME to THE ALREADY PLAYING USERS \n");
				RakNet::BitStream bsOut2;
				bsOut2.Write((MessageID)ID_PLAYER_JOINED_GAME);
				bsOut2.Write(mClientsMap[packet->systemAddress]);//ID
				bsOut2.Write(mGame->GetPlayerWithID(mClientsMap[packet->systemAddress])->GetName());//Send others players' name

				printf("My clients map size is %u \n", mClientsMap.size());
				for(unsigned int i=0; i<mClientsMap.size(); ++i)
				{
					if(GetClientAddressAt(i) != packet->systemAddress)
						mPeer->Send(&bsOut2,HIGH_PRIORITY,RELIABLE_ORDERED,0,GetClientAddressAt(i),false);
				}

				mNewPlayerJoining = false;
			}
			else
			{
				// If more than one player is ready (at least 2 players)
				// and if they both wants to play, start the game

				if(mClientsMap.size() != 1 && mClientsMap.size() == mPlayersReady)//tutti vogliono giocare
				{
					mGame->SetStarted(true);
					mNewPlayerJoining = false;
					for(UInt i=0; i<mClientsMap.size(); ++i)
					{
						printf("Sending ID_START_NEW_GAME to: %s \n", GetClientAddressAt(i).ToString());
						RakNet::BitStream bsOut;
						bsOut.Write((MessageID)ID_START_NEW_GAME);
						bsOut.Write(mClientsMap.size());//Tot players

						for(UInt j=0; j<mClientsMap.size(); ++j)
						{
							bsOut.Write(mGame->GetPlayerAt(j)->GetID());//ID
							bsOut.Write(mGame->GetPlayerAt(j)->GetName());//Send others players' name
						}

						mPeer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,GetClientAddressAt(i),false);
					}
				}

			}
		}
		break;

	default:
		printf("Message with identifier %i has arrived.\n", packet->data[0]);
		break;
	}
}

void Server::SendStartPacket(const RakNet::SystemAddress& iAddress)
{}

RakNet::SystemAddress Server::GetClientAddressAt(unsigned int iClient) const
{
	std::map<RakNet::SystemAddress, unsigned short>::const_iterator it = mClientsMap.begin();
	for(UInt i=0; i<iClient; ++i)
		++it;

	return it->first;
}

void Server::SendGameState(const RakNet::SystemAddress& iSystemAddress)
{
	if(!mGame->IsStarted())
		return;

	//////////////////////////////////
	// Use timestamp
	/////////////////////////////////
	RakNet::Time timeStamp = RakNet::GetTime();
	RakNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_TIMESTAMP);
	bsOut.Write(timeStamp);

	bsOut.Write((MessageID)ID_UPDATE_GAME_STATE);
	for(UInt i=0; i<mClientsMap.size(); ++i)
	{
		bsOut.Write(mGame->GetPlayerAt(i)->GetID());
		bsOut.Write(mGame->GetPlayerAt(i)->GetCannonRotation());
		bsOut.Write(mGame->GetPlayerAt(i)->GetLife());
		bsOut.Write(mGame->GetPlayerAt(i)->GetScore());
		bsOut.Write(mGame->GetPlayerAt(i)->GetPlayerDestroyed());
	}
	mPeer->Send(&bsOut,HIGH_PRIORITY,UNRELIABLE,0,iSystemAddress,false);

	// reset last player destroyed (on client will be another managment about it)
	for(int i=0; i<mClientsMap.size(); ++i)
		mGame->GetPlayerAt(i)->PlayerDestroyed("NONE");
}

void Server::SendUpdateProjectiles(const RakNet::SystemAddress& iSystemAddress)
{
	if(!mGame->IsStarted())
		return;

	//// send a packet only if there's a player with at least one projectile
	//bool oneBullet = false;
	//for(UInt i=0 ; i<GetPlayersNumber(); ++i)
	//{
	//	if(mGame->GetPlayerAt(i)->GetProjectilesSize()>0)
	//		oneBullet = true;
	//}

	//if(!oneBullet)
	//	return;

	//////////////////////////////////
	// Use timestamp
	/////////////////////////////////
	RakNet::Time timeStamp = RakNet::GetTime();
	RakNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_TIMESTAMP);
	bsOut.Write(timeStamp);
	bsOut.Write((MessageID)ID_UPDATE_PROJECTILES);
	for(UInt i=0; i<mClientsMap.size(); ++i)
	{
		bsOut.Write(mGame->GetPlayerAt(i)->GetID());
		bsOut.Write(mGame->GetPlayerAt(i)->GetProjectilesSize());
		for(UInt j=0; j<mGame->GetPlayerAt(i)->GetProjectilesSize(); ++j)
		{
			bsOut.Write(mGame->GetPlayerAt(i)->GetProjectileAt(j)->GetPos().X());
			bsOut.Write(mGame->GetPlayerAt(i)->GetProjectileAt(j)->GetPos().Y());
			float cosAlfa = phynet::math::Dot(Vector2(0,1), mGame->GetPlayerAt(i)->GetProjectileAt(j)->GetDirection());
			float angle = RadiansToDegree(std::acos(cosAlfa));
			if(mGame->GetPlayerAt(i)->GetProjectileAt(j)->GetDirection().X() < 0)
				angle*=-1;
			//printf("Angolo in gradi: %f \n", angle);
			bsOut.Write(angle);
		}
	}
	mPeer->Send(&bsOut,HIGH_PRIORITY,UNRELIABLE,0,iSystemAddress,false);

}

void Server::SendUpdateClients(unsigned short int playerIDdisconnected)
{
	//send the update to every player after a disconnection of one of them
	RakNet::Time timeStamp = RakNet::GetTime();
	RakNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_TIMESTAMP);
	bsOut.Write(timeStamp);
	bsOut.Write((MessageID)ID_UPDATE_CLIENTS);
	bsOut.Write(playerIDdisconnected);

	// before i had the match size of player number and clientMap
	for(std::map<RakNet::SystemAddress, unsigned short>::const_iterator it = mClientsMap.begin(); it != mClientsMap.end(); ++it)
	{
		// send the ID of the player who left the room
		mPeer->Send(&bsOut,HIGH_PRIORITY,UNRELIABLE,0,it->first,false);
	}
}

void Server::RemoveClient(const RakNet::SystemAddress& iClientAddress)
{
	std::map<RakNet::SystemAddress, unsigned short>::const_iterator disconnectedClient = mClientsMap.find(iClientAddress);
	//client->second is the ID associated to this iCLientAddress. It also is the position in the vector.
	unsigned short indexClientDisconnected = disconnectedClient->second;
	mGame->GetPlayerWithID(disconnectedClient->second)->SetActive(false);
	mGame->GetPlayerWithID(disconnectedClient->second)->RemoveAllProjectiles();
	//NB do not call erase before retrieving the client index
	mClientsMap.erase(iClientAddress);
	SendUpdateClients(indexClientDisconnected);
}
