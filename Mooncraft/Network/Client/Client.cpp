#include "Client.h"
#include "../Common/NetworkUtils.h"
#include "RakNetTypes.h"
#include "../../Game/Player.h"
#include "../../Input/InputMgr.h"
#include "GetTime.h"
#include <iostream>

#define SERVER_PORT 60000

void Client::Init(){

	// game initialization
	mGame = new GameClient();
	mGame->Init();
	mGame->DrawIntroMenu(true);

	mGameJoined = false;
	mGameStarted = false;

	mClock = sf::Clock();
	mClock.GetElapsedTime();

	mPacketCounter = 0;


	printf("Enter server IP or hit enter for 127.0.0.1\n");
	gets_s(str);
	if (str[0]==0){	 
		strcpy_s(str, "127.0.0.1");
	}
	printf("Starting the client.\n");
	peer->Connect(str, SERVER_PORT, 0,0);
}

Client::Client(void)
{

	peer = RakNet::RakPeerInterface::GetInstance();
	peer->Startup(1,&RakNet::SocketDescriptor(), 1);

	Init();
}



Client::~Client(void)
{
	RakNet::RakPeerInterface::DestroyInstance(peer);
}

unsigned char Client::GetPacketIdentifier(RakNet::Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(RakNet::Time)];
	else
		return (unsigned char) p->data[0];
}

void Client::SendPacket(unsigned char packetID)
{
	peer->DeallocatePacket(packet);
	packet = peer->Receive();
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)packetID);
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0, mServerAddress, false);
}


void Client::Run()
{

	while (mGame->WindowIsOpen())
	{

		if(!mGame->IsStarted())
			mGame->DrawIntroMenu(false);

		
		float elapsed = mClock.GetElapsedTime();
		mClock.Reset();

		sf::Event Event;
		while (mGame->GetWindow()->GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
			{
				Disconnect();
				mGame->GetWindow()->Close();
				return;
			}
		}

		ManageInput(elapsed);

		// network package receiving
		for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
		{
			ManagePacket(packet);
			mGame->ManagePacket(packet,peer);
		}

		// update of my game (projectiles)
		if(mGameStarted)
		{
			mGame->Update(elapsed);
			mGame->Draw();
		}
	}
}

void Client::Disconnect()
{
	//peer->DeallocatePacket(packet);
	//packet = peer->Receive();
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_DISCONNECTION_NOTIFICATION);
	bsOut.Write(mID);
	peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0, mServerAddress, false);
}
void Client::ManageInput(float iElapsed)
{
	if(mGame->GetInput()->IsKeyDown(sf::Key::J) && !mGameJoined)
	{
		/// client get the right ID of its GameClient
		mID = mGame->GetID();
		Vector2 position = mGame->CalculatePlayerPosition(mID);

		peer->DeallocatePacket(packet);
		packet = peer->Receive();//TO CHECK!!!! NECESSARIO??!?!?!
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)ID_CLIENT_WANNA_PLAY);
		bsOut.Write(position.X());
		bsOut.Write(position.Y());

		peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0, mServerAddress, false);
		mGameJoined = true;
	}

	/////////////////////////////
	//  Move Left handling
	////////////////////////////
	if(mGame->GetInput()->WasKeyDown(sf::Key::Left) && !mGame->GetInput()->IsKeyDown(sf::Key::Left))
	{
		///////////////////////////////
		//  Key Left has been released
		///////////////////////////////
		mGame->GetInput()->SetIsDownKey(sf::Key::Left, false);
		float deg = mGame->GetPlayerWithID(mID)->GetCannonRotation();
		peer->DeallocatePacket(packet);
		packet = peer->Receive();
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)ID_CLIENT_CANNON_LEFT_RELEASED);
		bsOut.Write(deg);
		peer->Send(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED,0, mServerAddress, false);
	}

	if(mGame->GetInput()->IsKeyDown(sf::Key::Left))
	{
		// grab my cannon degree
		float cannonDeg = mGame->GetPlayerWithID(mID)->GetCannonRotation();
		cannonDeg -= Player::ROTATION_SPEED * iElapsed;

		//if(cannonDeg < -Player::MAX_CANNON_DEGREE)
		//	cannonDeg = -Player::MAX_CANNON_DEGREE;

		mGame->GetPlayerWithID(mID)->SetCannonRotation(cannonDeg);
		//////////////////////////////////////
		// Check first if left was down...
		/////////////////////////////////////
		if(!mGame->GetInput()->WasKeyDown(sf::Key::Left))
		{

			peer->DeallocatePacket(packet);
			packet = peer->Receive();
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_CLIENT_CANNON_LEFT_PRESSED);
			bsOut.Write(cannonDeg);
			peer->Send(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED,0, mServerAddress, false);
		}

		/////////////////////////////////////////////
		// ..then store that now left key is Down
		////////////////////////////////////////////
		mGame->GetInput()->SetIsDownKey(sf::Key::Left, true);
	}

	/////////////////////////////
	//  Move Right handling
	////////////////////////////
	if(mGame->GetInput()->WasKeyDown(sf::Key::Right) && !mGame->GetInput()->IsKeyDown(sf::Key::Right))
	{
		mGame->GetInput()->SetIsDownKey(sf::Key::Right, false);
		float deg = mGame->GetPlayerWithID(mID)->GetCannonRotation();
		peer->DeallocatePacket(packet);
		packet = peer->Receive();
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)ID_CLIENT_CANNON_RIGHT_RELEASED);
		bsOut.Write(deg);
		peer->Send(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED,0, mServerAddress, false);
	}

	if(mGame->GetInput()->IsKeyDown(sf::Key::Right))
	{
		float cannonDeg = mGame->GetPlayerWithID(mID)->GetCannonRotation();
		cannonDeg += Player::ROTATION_SPEED * iElapsed;

		//if(cannonDeg > Player::MAX_CANNON_DEGREE)
		//	cannonDeg = Player::MAX_CANNON_DEGREE;

		mGame->GetPlayerWithID(mID)->SetCannonRotation(cannonDeg);

		//////////////////////////////////////
		// Check first if right was down...
		/////////////////////////////////////
		if(!mGame->GetInput()->WasKeyDown(sf::Key::Right))
		{

			peer->DeallocatePacket(packet);
			packet = peer->Receive();
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_CLIENT_CANNON_RIGHT_PRESSED);
			bsOut.Write(cannonDeg);
			peer->Send(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED,0, mServerAddress, false);
		}

		/////////////////////////////////////////////
		// ...then store that now right key is Down
		////////////////////////////////////////////
		mGame->GetInput()->SetIsDownKey(sf::Key::Right, true);
	}



	if(mGame->GetInput()->IsKeyDown(sf::Key::Space))
	{
		static float clockTime = 0.0f;
		clockTime += iElapsed;

		if(clockTime > 0.35f)
		{
			SendPacket((RakNet::MessageID)ID_CLIENT_SHOOT);
			clockTime= 0.0f;
		}
	}
}

void Client::ManagePacket(RakNet::Packet* iPacket)
{
	switch (GetPacketIdentifier(iPacket))
	{
	case ID_REMOTE_DISCONNECTION_NOTIFICATION:
		printf("Another client has disconnected.\n");
		break;
	case ID_REMOTE_CONNECTION_LOST:
		printf("Another client has lost the connection.\n");
		break;
	case ID_REMOTE_NEW_INCOMING_CONNECTION:
		printf("Another client has connected.\n");
		break;
	case ID_CONNECTION_REQUEST_ACCEPTED:
		{
			printf("Our connection request has been accepted.\n");

			printf("Please insert your name: \n");
			gets_s(mClientName);
			RakNet::RakString clientName;


			if (mClientName[0]==0)
				clientName = RakNet::RakString("Player");

			else
				clientName = mClientName;

			mServerAddress = iPacket->systemAddress;
			// Use a BitStream to write a custom user message
			// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically


			RakNet::BitStream bsOut;
			RakNet::Time timeStamp = RakNet::GetTime();
			bsOut.Write((RakNet::MessageID)ID_TIMESTAMP);
			bsOut.Write(timeStamp);
			bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
			bsOut.Write(clientName);
			bsOut.Write("Hello server, you got a new player");
			peer->Send(&bsOut,HIGH_PRIORITY,UNRELIABLE_SEQUENCED,0,iPacket->systemAddress,false);

			printf("Press J to JOIN the game (on game window)\n");

			
		}
		break;

	case ID_START_NEW_GAME:
		{
			int nPlayers = 0;
			RakNet::RakString clientName;
			unsigned short int clientID = 0;

			/// client get the right ID of its GameClient
			mID = mGame->GetID();
			//

			RakNet::BitStream bsIn(packet->data,iPacket->length,false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

			bsIn.Read(nPlayers);

			Vector2 position, direction;
			printf("I am starting a new game with %i players and my size is %i: \n", nPlayers, mGame->GetSizePlayers());

			for(int i=0; i<nPlayers; ++i)
			{
				bsIn.Read(clientID);
				bsIn.Read(clientName);

				printf("ClientID %u with name %s \n", clientID, clientName.C_String());
				position = mGame->CalculatePlayerPosition(clientID);
				direction = mGame->CalculatePlayerDirection(clientID);
				mGame->AddPlayer(new Player(clientName,clientID, position, direction));
			}
			mGameStarted = true;

		}
		break;

	case ID_PLAYER_JOINED_GAME:
		{
			unsigned short int clientID = 0;
			RakNet::RakString clientName = "SOMETHING WENT WRONG";

			RakNet::BitStream bsIn(packet->data,iPacket->length,false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(clientID);
			bsIn.Read(clientName);

			printf("New player with ID %u and name %s joined the game \n", clientID, clientName.C_String());

			Vector2 position, direction;
			position = mGame->CalculatePlayerPosition(clientID);
			direction = mGame->CalculatePlayerDirection(clientID);
			if(mGame->GetPlayersNumber() <= clientID)
			{
				mGame->AddPlayer(new Player(clientName,clientID, position, direction));
			}	
			else
			{
				mGame->GetPlayerAt(clientID)->Init(clientName,clientID, position, direction);
			}
		}
		break;
	}
}
