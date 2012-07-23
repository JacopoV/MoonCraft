#include <iostream>
#include "FSM.h"
#include "State.h"

FSM::FSM(GameInterface* iGame)
	:mGame(iGame),
	mCurrentState(NULL)
{

}

FSM::~FSM(void)
{	
}

void FSM::Dispatch(Event iEvent, CameraManager& iCamera)
{
	State* destState = FindState(mCurrentState->Transition(iEvent));
	if(destState != NULL)
	{
		if(destState != mCurrentState)
		{
			mCurrentState->OnExit(iCamera);  
			mCurrentState = destState; 
			mCurrentState->OnEnter(iCamera);
		}
	}
}

//void FSM::Update(INPUTACTION iAction, CameraManager& iCamera)
//{
//	if(mCurrentState != NULL)
//	{
//		mCurrentState->Update(iAction, iCamera);
//	}
//}

State* FSM::FindState(std::string iKey)
{
	return mStateMap[iKey];
}

State* FSM::GetCurrentState() const
{
	return mCurrentState;
}