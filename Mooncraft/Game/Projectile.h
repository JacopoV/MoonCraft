#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "../Common/Types.h"
#include "../Math/Vector2.h"
#include <string>
#include <vector>
#include <SFML/graphics.hpp>
#include "../Common/Interpolator.h"

class Projectile
{
public:
	typedef phynet::math::Vector2 Vector2;

	Projectile(const Vector2& iPos, const Vector2& iDirection, unsigned short int iParent);
	unsigned short int GetParent() const;
	Vector2 GetPos() const;
	Vector2 GetDirection() const;
	float GetSpeed() const;
	float GetRadius() const;
	int GetLife() const;
	void SetDirection(const Vector2&);
	void SetPosition(const Vector2&);
	void SetLife(int);
	void Update(float iElapsedTime);
	void Draw(sf::RenderWindow&, const sf::Color&) const;
	Interpolator* GetInterpolator() const;
	void Interpolate(float);

private:
	unsigned short int mParent;
	Vector2 mPos;
	Vector2 mDirection;
	float mSpeed;
	float mRadius;
	int mLife;
	Interpolator* mInterpolator;
};

#include "Projectile.inl"
#endif