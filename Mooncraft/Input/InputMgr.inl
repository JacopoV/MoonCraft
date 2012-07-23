inline InputMgr::InputMgr(const sf::Input* iInput)
	:
	mInput(iInput),
	mLastStateLeft(false),
	mLastStateRight(false),
	mLastStateSpace(false)
{}

inline bool InputMgr::IsKeyDown(sf::Key::Code iKey)
{
	return mInput->IsKeyDown(iKey);
}
