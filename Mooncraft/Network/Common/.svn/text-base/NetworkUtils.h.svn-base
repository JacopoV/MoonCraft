#pragma once
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "../../Math/Vector2.h"
#define PI 3.14159265

float lerpVector(float iFirst, float iSecond, float iStep);
phynet::math::Vector2 lerpVector(const phynet::math::Vector2& iFirst, const phynet::math::Vector2& iSecond, float iStep);


enum GameInput
{
	K_LEFT,
	K_RIGHT,
	K_UP,
	K_DOWN,
	K_SPACE,
	K_ESC
};

enum GameMessages
{
	ID_GAME_MESSAGE_1=ID_USER_PACKET_ENUM+1,
	ID_RETRIEVE,
	ID_START_NEW_GAME,
	ID_PLAYER_JOINED_GAME,
	ID_CLIENT_WANNA_PLAY,
	ID_CLIENT_CANNON_LEFT_PRESSED,
	ID_CLIENT_CANNON_LEFT_RELEASED,
	ID_CLIENT_CANNON_RIGHT_PRESSED,
	ID_CLIENT_CANNON_RIGHT_RELEASED,
	ID_CLIENT_SHOOT,
	ID_UPDATE_CANNON,
	ID_UPDATE_SHOOT,
	ID_UPDATE_GAME_STATE,
	ID_UPDATE_PROJECTILES,
	ID_UPDATE_CLIENTS,
	ID_GAME_OVER
};

inline unsigned char GetPacketIdentifier(const RakNet::Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(RakNet::Time)];
	else
		return (unsigned char) p->data[0];
}

inline float DegreeToRadians(float x)
{
	return static_cast<float>(x*PI/180);
}

inline float RadiansToDegree(float x)
{
	return static_cast<float>(x*180/PI);
}

inline float lerp(float iFirst, float iSecond, float iStep)
{
	if(iStep <= 0)
		return iFirst;
	
	if(iStep >= 1)
		return iSecond;

	return iFirst*(1-iStep) + iSecond*(iStep);
	//return iFirst + iStep * (iSecond - iFirst);
	//return iSecond; // DEBUG

}

inline phynet::math::Vector2 lerpVector(const phynet::math::Vector2& iFirst, const phynet::math::Vector2& iSecond, float iStep)
{
	return phynet::math::Vector2(lerp(iFirst.X(), iSecond.X(), iStep), lerp(iFirst.Y(), iSecond.Y(), iStep));
}




