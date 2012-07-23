#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include "Game.h"
#include "../Math/Vector2.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <sstream>

struct UpdatePacket{

	RakNet::Time timeStamp;
	std::vector<unsigned short int> dataID;
	std::vector<int> dataBullets;
	std::vector<std::vector<phynet::math::Vector2>> dataPosition;
	std::vector<float>dataDirection;

};

class InputMgr;


class GameClient : public Game
{
public:

	typedef phynet::UInt UInt;
	typedef phynet::math::Vector2 Vector2;

	void Init();
	int GetSizePlayers(){return mPlayers.size();}//TOREMOVE!!!!!!
	bool WindowIsOpen() const;
	InputMgr* GetInput() const;
	sf::RenderWindow* GetWindow() const;

	void ManagePacket(const RakNet::Packet*, RakNet::RakPeerInterface*);

	void Update(float dt);
	sf::Color GenerateShapeColor(int) const;
	
	void DrawIntroMenu(bool) const;
	void DrawStats() const;
	void DrawGameBoard() const;

	void Draw() const;

	Vector2 CalculatePlayerPosition(unsigned short id);
	Vector2 CalculatePlayerDirection(unsigned short id);

	unsigned short int GetID() const;
	
	~GameClient();


private:
	InputMgr* mInputManager;
	sf::RenderWindow* mWindow;
	int mWindowHeight; 
	int mWindowWidth;
	unsigned short int mID;
	sf::Font* mFont;

	UpdatePacket* mProjectilesUpdate [2];
	Vector2 CheckProjectilePosition(const Vector2&,Projectile*);
	Vector2 CalculateDirectionFromAngle(float iAngle);
	void StoreData(const RakNet::Packet&, int);
};


#include "GameClient.inl"

#endif