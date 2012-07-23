#include "Player.h"
#include "Projectile.h"

const float Player::MAX_RELOAD_TIMER = 1.0f;
const float Player::MAX_CANNON_DEGREE = 80.0f;
const float Player::ROTATION_SPEED = 30.5f;

void Player::Update(float iElapsed)
{
	mReloadTimer += iElapsed;

	for(int i=0; i<mProjectiles.size(); ++i)
		mProjectiles[i]->Update(iElapsed);
}

bool Player::Shoot()
{
	if(mReloadTimer >= MAX_RELOAD_TIMER)
	{
		mReloadTimer = 0;
   		mProjectiles.push_back(new Projectile(mPosition, mDirection, mID));
		return true;
	}

	return false;
}

void Player::Draw(sf::RenderWindow& iWindow, sf::Color& iColor, float timeElapsed) const
{
	if(!mIsActive)
		return;

	sf::Shape cannon;
	sf::Color regularColor = iColor;
	
	if(mLife < 30 && ((int)timeElapsed%2))
	{
		iColor.a -= 130;
	}
	


	// create the cannon shape
	cannon.AddPoint(0, 0, iColor, sf::Color(255, 255, 255));
	cannon.AddPoint(20, 0, iColor,   sf::Color(255, 255, 255));
	cannon.AddPoint(20, 20, iColor, sf::Color(255, 255, 255));
	cannon.AddPoint(15, 20, iColor, sf::Color(255, 255, 255));
	cannon.AddPoint(15, 40, iColor, sf::Color(255, 255, 255));
	cannon.AddPoint(5, 40, iColor, sf::Color(255, 255, 255));
	cannon.AddPoint(5, 20, iColor, sf::Color(255, 255, 255));
	cannon.AddPoint(0, 20, iColor, sf::Color(255, 255, 255));


	// Define an outline width
	cannon.SetOutlineWidth(2);

	// Disable filling and enable the outline
	cannon.EnableFill(true);
	cannon.EnableOutline(true);

	cannon.SetColor(sf::Color(255, 255, 255));

	/*cannon.Move(mPosition.X(), mPosition.Y());
	cannon.SetCenter(10,0);
	cannon.Rotate(mCannonRotation);*/

	// move and rotate the shape for each player
	cannon.Move(mPosition.X(), mPosition.Y());
	cannon.SetCenter(10,0);

	//switch(mID)
	//{

	//case 0:
	//	cannon.Rotate(mCannonRotation);
	//	break;
	//case 1:
	//	cannon.Rotate(mCannonRotation+90.0f);
	//	break;
	//case 2:
	//	cannon.Rotate(mCannonRotation+180.0f);
	//	break;
	//case 3:
	//	cannon.Rotate(mCannonRotation-90.0f);
	//	break;
	//}

	cannon.Rotate(mCannonRotation);


	// Draw the cannon
	iWindow.Draw(cannon);


	// draw projectiles
	for(int i=0; i<mProjectiles.size(); i++)
	{
		mProjectiles.at(i)->Draw(iWindow,regularColor);
	}


}

void Player::RemoveProjectileAt(int i)
{
	std::vector<Projectile*>::iterator it = mProjectiles.begin();
	mProjectiles.erase(it+i);
}

void Player::CheckCollisionWith(Player* iSecond)
{
	Projectile* first = NULL; 
	Projectile* second = NULL;

	for(int i=0; i<mProjectiles.size(); ++i)
	{
		first = mProjectiles[i];
		bool collision = false;
		for(int j=0; j<iSecond->GetProjectilesSize() && !collision; ++j)
		{
			second = iSecond->GetProjectileAt(j);
			if(Distance(first->GetPos(), second->GetPos()) < first->GetRadius() + second->GetRadius())
			{
				//Collision: for the moment remove
				if((mID != iSecond->GetID()))
				{
					collision = true;
					RemoveProjectileAt(i);
					iSecond->RemoveProjectileAt(j);
					--i;
					--j;
				}
				else if(mID == iSecond->GetID() && i != j)
				{
					collision = true;
					RemoveProjectileAt(i);
					//////////////// NB: in this case first and second ARE the same player.
					// Then we are removing TWO bullets of his.
					// If we remove first bullet at index i, with i>j:
					//
					// Before erase
					// [][][][][j][][][i] 
					// 
					// After erase
					// [][][][][j][][]   -----------> projectile after erase has still got index "j"
					//
					//
					// If index  i<j:
					// 
					// Before erase
					// [][i][][j]
					//
					// After erase
					// [][][j]         -----------> projectile after erase has got index "j - 1"


					if(i>j)
						iSecond->RemoveProjectileAt(j);
					else
						iSecond->RemoveProjectileAt(j-1);
				}
			}

		}

	}

}