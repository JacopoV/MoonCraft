#include "Projectile.h"
#include "../Network/Common/NetworkUtils.h"
#include "../Common/Interpolator.h"

void Projectile::Update(float iElapsedTime)
{
	mPos += mDirection * mSpeed * iElapsedTime;
}

void Projectile::Draw(sf::RenderWindow& iWindow, const sf::Color& iColor) const
{


	sf::Shape bullet = sf::Shape::Circle(sf::Vector2f(mPos.X(),mPos.Y()),8,iColor,2,sf::Color(255,255,255));
	//sf::Shape direction = sf::Shape::Line(mPos.X(), mPos.Y(), mPos.X() + mDirection.X() * 30, mPos.Y() + mDirection.Y() * 30, 1, sf::Color::White);

	bullet.EnableFill(true);
	bullet.EnableOutline(true);

	bullet.SetColor(sf::Color(255,255,255));

	iWindow.Draw(bullet);
	//iWindow.Draw(direction);
	
}

void Projectile::Interpolate(float iElapsed)
{
	mPos = mInterpolator->Interpolate(iElapsed);
}