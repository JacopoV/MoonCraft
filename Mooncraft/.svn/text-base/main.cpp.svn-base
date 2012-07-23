#include "RakPeerInterface.h"
#include "Phy\RigidBody2d.h"
#include "Math\Vector2.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include "Network\Server\Server.h"
#include "Network\Client\Client.h"
#include "Game\Projectile.h"

using namespace phynet::math;

Vector2 CheckProjectilePosition(const Vector2& iServerBullet , Projectile* iBullet)
{
	Vector2 result = iBullet->GetPos();
	float distance = Distance(iServerBullet,iBullet->GetPos()) * 0.1f;

	// grab the bullet local position (client prediction)
	Vector2 clientBullet = iBullet->GetPos();

	Vector2 joinVector = iServerBullet - clientBullet;
	joinVector.Normalize();

	if (Dot(joinVector,iBullet->GetDirection()) > 0) 
	{
		// in this case they have the same direction so i've to move my client bullet forward
		result += iBullet->GetDirection() * distance;

	}
	else
	{
		// in this case theye have different direction so i've to move my client bullet backward
		result -= iBullet->GetDirection() * distance;
	}

	//printf("X pos : %f \n",result.X());
	//printf("Y pos : %f \n",result.Y());
	//printf("dist : %F \n",distance);

	return result;

}

int main()
{

	//CheckProjectilePosition(Vector2(4,2),new Projectile(Vector2(3,0),Vector2(1,0),2));
	char str[512];
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	bool isServer;
	RakNet::Packet *packet;

	printf("(C) or (S)erver?\n");
	gets_s(str);

	if ((str[0]=='c')||(str[0]=='C'))
	{
		Client* client = new Client();
		client->Run();
		delete client;
	} else {
		Server * server = new Server();
		server->Run();
		delete server;
	}

	return EXIT_SUCCESS;


}