#include "Game.h"
#include "../Game/Player.h"
#include "../Game/Projectile.h"
#include "../Network/Common/NetworkUtils.h"
#include "BitStream.h"
#include "GetTime.h"

void Game::Update(float iElapsed)
{
	//Update players' cannon rotation
	for(int i=0; i<4; ++i)
	{
		if(IsTurningLeft[i])
		{
			GetPlayerWithID(i)->SetCannonRotation(GetPlayerWithID(i)->GetCannonRotation() - Player::ROTATION_SPEED * iElapsed);
		}

		if(IsTurningRight[i])
		{
			GetPlayerWithID(i)->SetCannonRotation(GetPlayerWithID(i)->GetCannonRotation() + Player::ROTATION_SPEED * iElapsed);
		}
	}

	//Update players' projectiles
	for(int i=0; i<mPlayers.size(); ++i)
		mPlayers[i]->Update(iElapsed);


	//Check collisions
	CheckPlayerCollision();
	CheckBoundryCollision();
	CheckProjectileCollision();
}

void Game::ManagePacket(const RakNet::Packet* iPacket, RakNet::RakPeerInterface* iPeer, unsigned short playerID)
{
	unsigned char messageID = GetPacketIdentifier(iPacket);
	float rotationSpeed = 0.2f;
	switch(messageID)
	{
	case ID_CLIENT_CANNON_LEFT_PRESSED:
		{
			IsTurningLeft[playerID] = true;
			ManageCannonUpdate(iPacket, iPeer, playerID, "CANNON_LEFT_PRESSED");
		}
		break;
	case ID_CLIENT_CANNON_LEFT_RELEASED:
		{
			IsTurningLeft[playerID] = false;
			ManageCannonUpdate(iPacket, iPeer, playerID, "CANNON_LEFT_RELEASED \n");
		}
		break;
	case ID_CLIENT_CANNON_RIGHT_PRESSED:
		{
			IsTurningRight[playerID] = true;
			ManageCannonUpdate(iPacket, iPeer, playerID, "CANNON_RIGHT_PRESSED \n");
		}
		break;
	case ID_CLIENT_CANNON_RIGHT_RELEASED:
		{
			IsTurningRight[playerID] = false;
			ManageCannonUpdate(iPacket, iPeer, playerID, "CANNON_RIGHT_RELEASED \n");
		}
		break;
	case ID_CLIENT_SHOOT:
		{
			printf("Player %u pressed CANNON_SHOOT \n", playerID);
			//////////////////////////////////
			// Use timestamp
			/////////////////////////////////
			RakNet::Time timeStamp = RakNet::GetTime();
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_TIMESTAMP);
			bsOut.Write(timeStamp);

			if(GetPlayerWithID(playerID)->Shoot())
			{
				bsOut.Write((RakNet::MessageID)ID_UPDATE_SHOOT);
				bsOut.Write(GetPlayerWithID(playerID)->GetCannonRotation());

				iPeer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,iPacket->systemAddress,false);
			}

		}
		break;
	}
}

void Game::ManageCannonUpdate(const RakNet::Packet* iPacket, RakNet::RakPeerInterface* iPeer, unsigned short playerID, const char* iMessage)
{
	RakNet::BitStream bsIn(iPacket->data, iPacket->length, false);
	float cannonDeg = 0;
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	bsIn.Read(cannonDeg);

	printf("Player %u is in %s", playerID, iMessage);
	GetPlayerWithID(playerID)->SetCannonRotation(cannonDeg);

	//RakNet::BitStream bsOut;
	//bsOut.Write((RakNet::MessageID)ID_UPDATE_CANNON);
	//bsOut.Write(cannonDeg);

	//iPeer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,iPacket->systemAddress,false);
}

void Game::ManageClientDisconnection(const RakNet::Packet* iPacket, RakNet::RakPeerInterface* iPeer)
{
	RakNet::BitStream bsIn(iPacket->data, iPacket->length, false);
	unsigned short int playerID = -1;
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	bsIn.Read(playerID);

	// here i've the ID of the disconnected player
	printf("The player with ID %u has disconnected\n", playerID);

	if( mPlayers.size() >0 )
	{
		
		std::vector<Player*> backupPlayers;
		for(int i=0; i<mPlayers.size(); i++)
		{
			if(mPlayers.at(i)->GetID() != playerID)
			{
				backupPlayers.push_back(mPlayers.at(i));
			}
			else
				delete mPlayers.at(i);
		}

		// here in backupPlayers i've the remaining player
		
		// CLEANUP
		while(mPlayers.size())
			mPlayers.pop_back();
		
		for(int i=0; i<backupPlayers.size(); i++)
			mPlayers.push_back(backupPlayers.at(i));


		

	}

}

Player* Game::GetPlayerWithID(unsigned short iID) const
{
	for(int i=0; i<mPlayers.size(); ++i)
	{
		if(mPlayers[i]->GetID() == iID)
			return mPlayers[i];
	}

	return NULL;
}

void Game::CheckPlayerCollision()
{

	for(int i=0; i<mPlayers.size(); ++i)
	{
		for(int j=0; j<mPlayers[i]->GetProjectilesSize(); ++j)
		{
			Projectile* currentProj = mPlayers[i]->GetProjectileAt(j);

			//Check if collision with a player. If so, remove it
			for(int k = 0; k<mPlayers.size(); ++k)
			{
				if( currentProj->GetParent() != mPlayers[k]->GetID() && Distance(currentProj->GetPos(), mPlayers[k]->GetPosition()) < currentProj->GetRadius() + 10.0f)
				{
					mPlayers[i]->RemoveProjectileAt(j);
					--j;

					// Add a point
					mPlayers[i]->SetScore(mPlayers[i]->GetScore()+10);


					if(mPlayers[k]->GetLife()>0)
					{
						mPlayers[k]->SetLife(mPlayers[k]->GetLife()-10);
						
					}
					if(mPlayers[k]->GetLife()==0)
					{
							// "i" player destroyed the "k" player -> extra points
							mPlayers[i]->SetScore(mPlayers[i]->GetScore()+30);
							mPlayers[i]->PlayerDestroyed(mPlayers[k]->GetName());

							// here the player K can't play


					}
				}
			}
		}
	}
}

void Game::CheckBoundryCollision()
{
	for(int i=0; i<mPlayers.size(); ++i)
	{
		for(int j=0; j<mPlayers[i]->GetProjectilesSize(); ++j)
		{
			Projectile* currentProj = mPlayers[i]->GetProjectileAt(j);
			
			if(currentProj->GetPos().X() > MAX_BOUNDRY_X)
			{
				currentProj->GetPos().X() = MAX_BOUNDRY_X;
				currentProj->SetDirection(Vector2(-currentProj->GetDirection().X(), currentProj->GetDirection().Y()));
				currentProj->SetLife(currentProj->GetLife()-1);
			}
			else if(currentProj->GetPos().X() < 0)
			{
				currentProj->GetPos().X() = 0.0f;
				currentProj->SetDirection(Vector2(-currentProj->GetDirection().X(), currentProj->GetDirection().Y()));
				currentProj->SetLife(currentProj->GetLife()-1);
			}

			if(currentProj->GetPos().Y() > MAX_BOUNDRY_Y)
			{
				currentProj->GetPos().Y() = MAX_BOUNDRY_Y;
				currentProj->SetDirection(Vector2(currentProj->GetDirection().X(), -currentProj->GetDirection().Y()));
				currentProj->SetLife(currentProj->GetLife()-1);
			}
			else if(currentProj->GetPos().Y() < 0)
			{
				currentProj->GetPos().Y() = 0.0f;
				currentProj->SetDirection(Vector2(currentProj->GetDirection().X(), -currentProj->GetDirection().Y()));
				currentProj->SetLife(currentProj->GetLife()-1);
			}

			if(currentProj->GetLife() <= 0)
				mPlayers[i]->RemoveProjectileAt(j);
		}
	}
}


void Game::CheckProjectileCollision()
{
	for(int i=0; i<mPlayers.size(); ++i)
	{
		for(int j=0; j<mPlayers.size(); ++j)
		{
			mPlayers[i]->CheckCollisionWith(mPlayers[j]);
		}
	}
}
