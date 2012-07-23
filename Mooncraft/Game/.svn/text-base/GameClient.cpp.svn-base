#include "GameClient.h"
#include "Player.h"
#include "Projectile.h"
#include "../Network/Common/NetworkUtils.h"
#include "BitStream.h"
#include "../Input/InputMgr.h"
#include "../Common/Interpolator.h"




void GameClient::Init()
{
	mWindowWidth = 800;
	mWindowHeight = 600;
	mWindow = new sf::RenderWindow(sf::VideoMode(mWindowWidth, mWindowHeight), "MoonCraft");
	mFont = new sf::Font();

	if (!mFont->LoadFromFile("C:/Windows/Fonts/arial.ttf", 50))
	{
		printf("Error while loading font\n");
	}


	mProjectilesUpdate[0] = mProjectilesUpdate[1] = NULL;

	mInputManager = new InputMgr(&mWindow->GetInput());


}


void GameClient::Update(float iElapsed)
{
	// update the interpolator for every projectiles
	for(unsigned int i=0; i<mPlayers.size(); ++i)
	{
		if(mPlayers[i]->IsActive())
		{
			for(int k=0; k<mPlayers[i]->GetProjectilesSize(); ++k)
			{
				mPlayers[i]->GetProjectileAt(k)->Interpolate(iElapsed);
			}
		}
	}
}


void GameClient::StoreData(const RakNet::Packet& iPacket, int index)
{
	unsigned short int ID = 0;
	int nBullets = 0;
	float positionX = 0;
	float positionY = 0;
	float direction = 0;
	RakNet::Time timeStamp;

	RakNet::BitStream bsIn(iPacket.data,iPacket.length,false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	bsIn.Read(timeStamp);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

	mProjectilesUpdate[index] = new UpdatePacket();
	UpdatePacket* pkt = mProjectilesUpdate[index];

	// store all packeage data in the buffer
	pkt->timeStamp = timeStamp;

	for(unsigned int i=0; i<mPlayers.size(); ++i)
	{
		// read data
		bsIn.Read(ID);
		bsIn.Read(nBullets);

		// store data
		pkt->dataID.push_back(ID);
		pkt->dataBullets.push_back(nBullets);

		std::vector<Vector2> positions;

		for(int k=0; k<nBullets; ++k)
		{
			// read data
			bsIn.Read(positionX);
			bsIn.Read(positionY);
			bsIn.Read(direction);

			// store data
			positions.push_back(Vector2(positionX,positionY));
			pkt->dataDirection.push_back(direction);
		}

		// store the positions
		pkt->dataPosition.push_back(positions);

	}

}


// get the bullet position (X,Y) from the server and correct the position of my bullet
GameClient::Vector2 GameClient::CheckProjectilePosition(const Vector2& iServerBullet , Projectile* iClientBullet)
{
	Vector2 result = iClientBullet->GetPos();
	float posX = result.X();
	float posY = result.Y();

	float distance = Distance(iServerBullet,iClientBullet->GetPos()) * 0.1f;

	Vector2 joinVector = iClientBullet->GetPos() - iServerBullet;
	joinVector.Normalize();

	if (Dot(joinVector,iClientBullet->GetDirection()) > 0) 
	{
		// in this case they have the same direction so i've to move my client bullet forward
		posX += distance;
		posY += distance;
	}
	else
	{
		// in this case theye have different direction so i've to move my client bullet backward
		posX -= distance;
		posY -= distance;
	}
	return Vector2(posX,posY);

}


void GameClient::ManagePacket(const RakNet::Packet* iPacket, RakNet::RakPeerInterface* iPeer)
{
	unsigned char messageID = GetPacketIdentifier(iPacket);
	switch(messageID)
	{
	case ID_UPDATE_GAME_STATE:
		{
			unsigned short int id = 0;
			float cannonDegree = 0.0f;
			UInt playerLife = 100;
			UInt playerScore = 0;
			RakNet::Time timeStamp;
			RakNet::RakString playerDestroyed;

			RakNet::BitStream bsIn(iPacket->data,iPacket->length,false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(timeStamp);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

			for(unsigned int i=0; i<mPlayers.size(); ++i)
			{
				bsIn.Read(id);
				bsIn.Read(cannonDegree);
				bsIn.Read(playerLife);
				bsIn.Read(playerScore);
				bsIn.Read(playerDestroyed);

				Player* player = GetPlayerWithID(id);

				/////////////////////////////////
				//  Apply a little smoothing
				/////////////////////////////////
				float difference = abs(player->GetCannonRotation() - cannonDegree);

				if(difference > 25.0f)
					player->SetCannonRotation(cannonDegree);
				else if (difference > 0.1f)
				{
					if(cannonDegree < player->GetCannonRotation())
						difference = -difference;
					player->SetCannonRotation(player->GetCannonRotation() + difference * 0.5f);
				}

				player->SetLife(playerLife);
				player->SetScore(playerScore);
				player->PlayerDestroyed(playerDestroyed);

			}

		}
		break;

	case ID_UPDATE_CANNON : 
		{
			//float cannonDegree = 0.0f;
			//RakNet::Time timeStamp;

			//RakNet::BitStream bsIn(iPacket->data,iPacket->length,false);
			//bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			//bsIn.Read(timeStamp);
			//bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

			//bsIn.Read(cannonDegree);

			//// update my cannon rotation
			//GetPlayerWithID(mID)->SetCannonRotation(cannonDegree);

		}
		break;

	case ID_RETRIEVE :
		{
			unsigned short int ID = NULL;
			RakNet::Time timeStamp;

			RakNet::BitStream bsIn(iPacket->data,iPacket->length,false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(timeStamp);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

			bsIn.Read(ID);

			// save my ID retreived from the server
			mID = ID;


		}
		break;

	case ID_UPDATE_SHOOT :
		{
			float cannonDegree = 0.0f;
			RakNet::Time timeStamp;

			RakNet::BitStream bsIn(iPacket->data,iPacket->length,false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(timeStamp);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(cannonDegree);

			// update my rotation to update my direction for the projectiles
			Player* player = GetPlayerWithID(mID);
			player->SetCannonRotation(cannonDegree);

			// create the projectile in the right position
			Vector2 playerPos = Vector2(player->GetPosition().X(),player->GetPosition().Y()); 
			Vector2 playerDir = Vector2(player->GetDirection().X(),player->GetDirection().Y());

			Projectile* bullet = new Projectile(playerPos,playerDir,mID);
			player->Shoot(bullet);
		}
		break;


	case ID_UPDATE_PROJECTILES :
		{
			if(mProjectilesUpdate[0]==NULL)
			{
				// store the FIRST PACKET
				StoreData(*iPacket,0);
			}
			else
			{
				// I've read the first packet
				// so i add in the struct only at last position 
				StoreData(*iPacket,1);

				// manage data
				for(unsigned int i=0; i<mPlayers.size(); ++i)
				{
					// grab the data information from the last packet sent from the server
					UpdatePacket* pkt = mProjectilesUpdate[1];
					Player* player = GetPlayerWithID(pkt->dataID.at(i));
					int playerBullets = player->GetProjectilesSize();
					int nBullets = pkt->dataBullets.at(i);
					bool backToTheFuture = false;


					if(playerBullets < nBullets)
					{
						//here i need to push a new projectile (server has the truth)
						int difference =  nBullets - playerBullets;
						while (difference)
						{
							//fake projectile -> next will be updated with values from the server
							Projectile* bullet = new Projectile(player->GetPosition(),player->GetDirection(),player->GetID());
							player->Shoot(bullet);
							difference--;
						}

					}

					if(playerBullets > nBullets)
					{
						//for(int k=0; k<playerBullets; ++k)
						//{
						//	printf("rimuovo : %f / %f \n",player->GetProjectileAt(k)->GetPos().X(),player->GetProjectileAt(k)->GetPos().Y());
						//}

						//here i need to pop a  projectile (server has the truth)
						int difference = playerBullets - nBullets;
						while (difference)
						{
							player->Remove();
							difference--;
						}
						backToTheFuture = true;
					}

					// here i've to update the right position of the bullets using lerp
					UpdatePacket* pktA = mProjectilesUpdate[0];
					UpdatePacket* pktB = mProjectilesUpdate[1];

					for(int k=0; k<nBullets; ++k)
					{

						RakNet::Time deltaTime = pktB->timeStamp  - pktA->timeStamp;
						float timeElapsed = (float)deltaTime; // ?????? CHECK IF THE CAST IS OK ??????

						// need to calculate the distance betweet the point A and point B
						float distance = Distance(player->GetProjectileAt(k)->GetPos(),pktB->dataPosition.at(i).at(k)); // GROSSI PROBLEMI CON RIMOZIONE PROIETTILI!!!

						// spazio / tempo -> step
						float velocity = 0.55f / distance;
						//  distance / time --> time è il tempo entro cui il client riceverà la prossima update dal server
						// è necessario interpolare il proiettile fino alla nuova posizione
						// prima che arrivi la nuova update

						Projectile* bullet = player->GetProjectileAt(k);
						Interpolator* bulletInterpolator = bullet->GetInterpolator();


						if(backToTheFuture)
						{
							Vector2 oldPos = pktB->dataPosition.at(i).at(k);  // prende la posizione del proiettile che dovrebbe essere rimosso
							Vector2 direction(std::sin(pktB->dataDirection[k]),std::cos(pktB->dataDirection[k]));
							oldPos -= direction * bullet->GetSpeed() * timeElapsed/1000;
							//bullet->SetDirection(direction);
							bulletInterpolator->SetData(oldPos,pktB->dataPosition.at(i).at(k), 1.0f);

						}
						else
						{
							float X, Y, angle;
							angle = DegreeToRadians(abs(pktB->dataDirection[k]));
							//printf("Angolo in gradi: %f \n", pktB->dataDirection[k]);
							X = std::sin(angle);
							Y = std::cos(angle);
							//printf("X: %f Y: %f \n", X, Y);

							if(pktB->dataDirection[k] < 0)
								X*=-1;

							if(angle > 90)//abs(pktB->dataDirection[k]) > 90
								Y*=-1;

							bullet->SetDirection(Vector2(X,Y).Normalize());
							bulletInterpolator->SetData(player->GetProjectileAt(k)->GetPos(),pktB->dataPosition.at(i).at(k), 3.0f);
						}

						//printf("Time Elapsed btween packets: %f \n", timeElapsed);
						//printf("Distance: %f \n", distance);
						//printf("La velocità è %f \n", velocity);

						// set interpolator data into the "k" bullet
						//Vector2 lullaby (player->GetProjectileAt(k)->GetPos());
						//Vector2 lullamelol (pktB->dataPosition.at(i).at(k));

						//bulletInterpolator->SetData(player->GetProjectileAt(k)->GetPos(),pktB->dataPosition.at(i).at(k), 3.0f);

						// set direction
						//float degree = DegreeToRadians(pktB->dataDirection.at(k));
						//bullet->SetDirection(Vector2(std::sin(degree-player->GetID()*90),std::cos(degree-player->GetID()*90)));

					}

				}


				// clean the buffer in the first position
				delete mProjectilesUpdate[0];

				// swap the addrees for the last received packet
				mProjectilesUpdate[0] = mProjectilesUpdate[1];
				mProjectilesUpdate[1] = NULL;

			}

		}

		break;

	case ID_UPDATE_CLIENTS:
		{

			RakNet::Time timeStamp;
			//int playersNumber;
			unsigned short int removeID = -1;

			RakNet::BitStream bsIn(iPacket->data,iPacket->length,false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(timeStamp);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(removeID);

			printf("Player with ID %i has disconnected \n", removeID);

			for(unsigned int i=0; i< mPlayers.size(); ++i)
			{
				if(mPlayers.at(i)->GetID()==removeID)
				{
					mPlayers.at(i)->SetActive(false);
					mPlayers.at(i)->RemoveAllProjectiles();
				}		
			}
		}
		break;
	}

}

sf::Color GameClient::GenerateShapeColor(int ID) const
{

	sf::Color color;

	switch(ID){

	case 0 :
		// red
		color = sf::Color(255,0,0);
		break;
	case 1:
		// yellow
		color = sf::Color(255,255,0);
		break;
	case 2:
		// cian
		color = sf::Color(0,255,255);
		break;
	case 3:
		// purple
		color = sf::Color(255,0,255);
		break;
	case -1:
		// white
		color = sf::Color(255,255,255);
		break;

	}

	return color;

}

void GameClient::DrawIntroMenu(bool flag) const
{

	mWindow->Clear();

	sf::String moon= sf::String("M O O N ", *mFont, 55);
	sf::String craft= sf::String("C R A F T", *mFont, 55);
	sf::String join = sf::String("press to (J)oin", *mFont, 35);

	sf::Shape cannon;

	moon.SetColor(GenerateShapeColor(-1));
	moon.Move(170,30);

	craft.SetColor(GenerateShapeColor(0));
	craft.Move(400,30);

	join.SetColor(GenerateShapeColor(-1));
	join.Move(300,130);

	mWindow->Draw(moon);
	mWindow->Draw(craft);
	mWindow->Draw(join);

	sf::Color iColor = GenerateShapeColor(0);

	// create the cannon shape
	cannon.AddPoint(0, 0, iColor, GenerateShapeColor(-1));
	cannon.AddPoint(20, 0, iColor,   GenerateShapeColor(-1));
	cannon.AddPoint(20, 20, iColor, GenerateShapeColor(-1));
	cannon.AddPoint(15, 20, iColor, GenerateShapeColor(-1));
	cannon.AddPoint(15, 40, iColor, GenerateShapeColor(-1));
	cannon.AddPoint(5, 40, iColor, GenerateShapeColor(-1));
	cannon.AddPoint(5, 20, iColor, GenerateShapeColor(-1));
	cannon.AddPoint(0, 20, iColor, GenerateShapeColor(-1));


	// Define an outline width
	cannon.SetOutlineWidth(2);


	cannon.EnableFill(true);
	cannon.EnableOutline(true);
	cannon.SetColor(GenerateShapeColor(-1));


	cannon.SetCenter(10,0);
	cannon.Scale(10,10);
	cannon.Move(780, 700);
	cannon.Rotate(-147);

	mWindow->Draw(cannon);
	if(flag)
		mWindow->Display();

}


void GameClient::DrawStats() const
{
	// Load the font from a file

	sf::String playerText;
	sf::String playerInfo;
	sf::String bulletText;
	sf::String bulletInfo;
	sf::String lifeText;
	sf::String lifeInfo;
	sf::String scoreText;
	sf::String scoreInfo;
	sf::String dangerText;
	sf::String playerDestroyedText;
	sf::String playerDestroyedInfo;


	std::stringstream prjSize;
	std::stringstream playerLife;
	std::stringstream playerScore;
	prjSize << GetPlayerWithID(mID)->GetProjectilesSize();
	playerLife << GetPlayerWithID(mID)->GetLife();

	playerText = sf::String("Player : ", *mFont, 15);
	playerInfo = sf::String(GetPlayerWithID(mID)->GetName().C_String(), *mFont, 15);
	bulletText = sf::String("Bullets : ", *mFont, 15);
	bulletInfo = sf::String(prjSize.str(), *mFont, 15);
	lifeText   = sf::String("Life : ", *mFont, 15);
	lifeInfo   = sf::String(playerLife.str(), *mFont, 15);
	scoreText  = sf::String("Score : ", *mFont,15);
	playerScore << GetPlayerWithID(mID)->GetScore();
	scoreInfo  = sf::String(playerScore.str(), *mFont, 15);
	dangerText = sf::String("DANGER! LOW ENERGY ",*mFont,15);
	playerDestroyedText = sf::String("YOU DESTROYED -> ", *mFont, 15);


	// text setup
	playerText.SetColor(GenerateShapeColor(mID));
	playerText.Move(10.f,10.f);

	playerInfo.SetColor(GenerateShapeColor(mID));
	playerInfo.Move(70.f,10.f);

	bulletText.SetColor(GenerateShapeColor(mID));
	bulletText.Move(10.f,25.f);

	bulletInfo.SetColor(GenerateShapeColor(mID));
	bulletInfo.Move(70.f,25.f);

	lifeText.SetColor(GenerateShapeColor(mID));
	lifeText.Move(10.f,40.f);

	lifeInfo.SetColor(GenerateShapeColor(mID));
	lifeInfo.Move(70.f,40.f);

	scoreText.SetColor(GenerateShapeColor(mID));
	scoreText.Move(10.f,55.f);

	scoreInfo.SetColor(GenerateShapeColor(mID));
	scoreInfo.Move(70.f,55.f);

	dangerText.SetColor(GenerateShapeColor(mID));
	dangerText.Move(10.f,70.f);

	playerDestroyedText.SetColor(GenerateShapeColor(mID));
	playerDestroyedText.Move(10.f,580.f);

	// draw
	mWindow->Draw(playerText);
	mWindow->Draw(playerInfo);
	mWindow->Draw(bulletText);
	mWindow->Draw(bulletInfo);
	mWindow->Draw(lifeText);
	mWindow->Draw(lifeInfo);
	mWindow->Draw(scoreText);
	mWindow->Draw(scoreInfo);

	if(GetPlayerWithID(mID)->GetLife()<30 && (int)mClock.GetElapsedTime()%2)
		mWindow->Draw(dangerText);

	static sf::Clock localClock;
	static RakNet::RakString playerName = "NONE";

	if(GetPlayerWithID(mID)->GetPlayerDestroyed() != "NONE" )
	{
		playerName = GetPlayerWithID(mID)->GetPlayerDestroyed();
		localClock.Reset();
	}

	if(playerName != "NONE")
	{
		playerDestroyedInfo = sf::String(playerName.C_String(), *mFont, 15);
		playerDestroyedInfo.SetColor(GenerateShapeColor(mID));
		playerDestroyedInfo.Move(170.f,580.f);
		mWindow->Draw(playerDestroyedText);
		mWindow->Draw(playerDestroyedInfo);

		if(localClock.GetElapsedTime() > 10.0f)
		{
			// reset the stat about enemy
			playerName = "NONE";
		}
	}
}

void GameClient::DrawGameBoard() const
{
	sf::Shape boardLine;
	sf::Color white = GenerateShapeColor(-1);

	boardLine.AddPoint(3, 3, white, white);
	boardLine.AddPoint(mWindowWidth-3, 3, white,  white);
	boardLine.AddPoint(mWindowWidth-3, mWindowHeight-3, white);
	boardLine.AddPoint(3, mWindowHeight-3, white, white);

	boardLine.SetOutlineWidth(3);

	boardLine.EnableFill(false);
	boardLine.EnableOutline(true);

	mWindow->Draw(boardLine);

}


void GameClient::Draw() const
{
	mWindow->Clear();

	DrawGameBoard();

	if(mPlayers.size()!=0)
		DrawStats();

	// call the draw to the player (if it has projectlis, draws them)
	for(unsigned int i=0; i<mPlayers.size(); i++)
		mPlayers.at(i)->Draw(*mWindow,GenerateShapeColor(mPlayers.at(i)->GetID()),mClock.GetElapsedTime());
	// Finally, display the rendered frame on screen



	mWindow->Display();

	// Start game loop
	/*Vector2 positionShape = Vector2(0,0);
	float x = 0;
	float y = 0;*/

	//phynet::phy::RigidBody2D rigidBody;


	////////////////////////////
	////	RIGID BODY CREATION
	////////////////////////////
	//phynet::Real i_mass = 5;
	//phynet::Real i_inertiaTensor = 5;
	//phynet::Real i_linearDamping = 5;
	//phynet::Real i_angularDamping = 5; 
	//phynet::Real i_elasticity = 5; 
	//Vector2 i_pos = Vector2(0,0); 
	//Vector2 i_linearVel = Vector2(1,0);
	//Vector2 i_orientation = Vector2(1,0);
	//phynet::Real i_angularVelocity = 0;


	/*Polygon2 i_shape;
	phynet::math::Polygon2::Points points;
	points.push_back(Vector2(0, 0));
	points.push_back(Vector2(79, 0));
	points.push_back(Vector2(79, 79));
	points.push_back(Vector2(0, 79)); 

	i_shape.SetPoints(points);*/

	/*rigidBody.Init(i_mass, 
	i_inertiaTensor, 
	i_linearDamping, 
	i_angularDamping,
	i_elasticity,
	i_pos,
	i_linearVel,
	i_orientation,
	i_angularVelocity,
	i_shape);*/

	//rigidBody.GetShape().GetPoints();

	//// We can still use the functions common to all SFML drawable objects
	//x+=0.001;
	//y+=0.0001;
	//positionShape.Set(x,y);
	//rigidBody.Move(positionShape);
	//
}

GameClient::Vector2 GameClient::CalculatePlayerPosition(unsigned short iID)
{
	Vector2 result;

	switch(iID)
	{
	case 0:
		// nord
		result = Vector2(mWindowWidth/2.0f , 5.0f);
		break;
	case 1:
		// est
		result = Vector2(mWindowWidth - 5.0f , mWindowHeight/2.0f );
		break;
	case 2:
		// sud
		result = Vector2(mWindowWidth/2.0f, mWindowHeight - 5.0f);
		break;
	case 3:
		// west
		result = Vector2(5.0f, mWindowHeight/2.0f );
		break;
	}
	return result;
}

GameClient::Vector2 GameClient::CalculatePlayerDirection(unsigned short iID)
{
	Vector2 result(0,0);
	switch(iID)
	{
	case 0:
		// nord
		result.Set(0, 1);
		break;
	case 1:
		// est
		result.Set(-1, 0);
		break;
	case 2:
		// sud
		result.Set(0, -1);
		break;
	case 3:
		// west
		result.Set(1, 0);
		break;
	}

	return result;
}

unsigned short int GameClient::GetID() const{

	return mID;

}

GameClient::~GameClient()
{

	//delete mWindow;
	//delete mInput;


}