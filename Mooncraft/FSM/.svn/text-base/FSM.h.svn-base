#pragma once
#include "State.h"
#include <map>

class GameInterface;

class FSM
{
public:
	FSM(GameInterface* iGame);
	~FSM(void);
	void Dispatch(Event, CameraManager&);
	//void Update(INPUTACTION iAction, CameraManager& iCamera);
	void SetState(State* iState);
	State* GetCurrentState() const;

private:
	State* mCurrentState;
	GameInterface* mGame;
	std::map<std::string, State*> mStateMap;
	State* FindState(std::string);
	
};

