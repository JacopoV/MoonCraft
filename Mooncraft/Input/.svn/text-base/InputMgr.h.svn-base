#ifndef INPUT_MGR_H
#define INPUT_MGR_H

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class InputMgr
{
public:
	InputMgr(const sf::Input*);
	~InputMgr(void);

	bool Init(sf::Input*);
	bool IsKeyDown(sf::Key::Code);
	bool WasKeyDown(sf::Key::Code);
	void SetIsDownKey(sf::Key::Code, bool);

private:
	bool mLastStateLeft;
	bool mLastStateRight;
	bool mLastStateSpace;
	const sf::Input* mInput;
};

#include "InputMgr.inl"
#endif