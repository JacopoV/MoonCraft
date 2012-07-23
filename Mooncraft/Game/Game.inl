//////////////////////////////////////
//   Game.inl
//////////////////////////////////////

inline Game::Game()
	:mIsStarted(false)
{
	//TODO
	Init();
}

inline Game::~Game()
{
	//todo
}

inline bool Game::Init()
{
	//TODO
	for(int i=0; i<4; ++i)
	{
		IsTurningLeft[i] = false;
		IsTurningRight[i] = false;
	}
	return true;
}

inline void Game::AddPlayer(Player* iPlayer)
{
	mPlayers.push_back(iPlayer);
}

inline Player* Game::GetPlayerAt(int i) const
{
	return mPlayers[i];
}

inline void Game::SetStarted(bool iStarted)
{
	mIsStarted = iStarted;
}

inline bool Game::IsStarted() const
{
	return mIsStarted;
}

inline int Game::GetPlayersNumber() const
{
	return mPlayers.size();
}

inline void Game::RemovePlayerAt(int i)
{
	std::vector<Player*>::const_iterator it = mPlayers.begin() + i;
	mPlayers.erase(it);
}


