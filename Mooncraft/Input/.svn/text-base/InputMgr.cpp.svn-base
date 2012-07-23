#include "InputMgr.h"

bool InputMgr::WasKeyDown(sf::Key::Code iKey)
{
	bool keyFound = false;
	switch (iKey)
	{
	case sf::Key::Left:
		{
			return mLastStateLeft;
		}
		break;
	case sf::Key::Right:
		{
			return mLastStateRight;
		}
		break;
	case sf::Key::Space:
		{
			return mLastStateSpace;
		}
		break;
	}

	if(!keyFound)
		printf("Non hai aggiunto mLastKeyState all'input manager!");
	return false;
}

void InputMgr::SetIsDownKey(sf::Key::Code iKey, bool isDown)
{
	bool keyFound = false;
	switch (iKey)
	{
	case sf::Key::Left:
		{
			mLastStateLeft = isDown;
			keyFound = true;
		}
		break;
	case sf::Key::Right:
		{
			mLastStateRight = isDown;
			keyFound = true;
		}
		break;
	case sf::Key::Space:
		{
			mLastStateSpace = isDown;
			keyFound = true;
		}
		break;
	}

	if(!keyFound)
		printf("Non hai aggiunto mLastKeyState all'input manager!");
}