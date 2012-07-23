#include "State.h"
#include "FSM.h"
#include <string>


State::State(GameInterface* iGame, FSM& iFSM, int iId)
	:mGame(iGame),
	mFSM(&iFSM),
	mId(iId)
{
}

State::~State(void)
{
}

std::string State::Transition(Event iEvent)
{
	return mTransitionTable[iEvent];
}

const int State::GetID() const
{
	return mId;
}

//void State::AddAction(InputActionInfo iInfo)
//{
//	mInputInfo = iInfo;
//}