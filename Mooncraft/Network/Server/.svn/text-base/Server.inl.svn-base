inline void Server::AddClient(const RakNet::SystemAddress& iClientAddress)
{
	if(mClientsMap.size()>4)
		return;//no more space for new players

	bool IDArray[] = {true, true, true, true};//0,1,2,3
	//Search for ID already in use
	for(std::map<RakNet::SystemAddress, unsigned short>::const_iterator it = mClientsMap.begin(); it != mClientsMap.end(); ++it)
	{
		IDArray[it->second] = false;
	}
	int freeID = -1;
	for(int i=0; i<4 && freeID == -1; ++i)
	{
		if(IDArray[i])
		{
			freeID = i;
		}
	}

	mClientsMap[iClientAddress] = freeID;
}

inline void Server::RemoveAllClients()
{
	mClientsMap.clear();
}

inline int Server::GetPlayersNumber() const
{
	return mClientsMap.size();
}