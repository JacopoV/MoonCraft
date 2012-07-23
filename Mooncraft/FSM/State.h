#ifndef STATE_H
#define STATE_H

#include <string>
#include <map>

enum Event
{
	E_STARTED,//Before launching the ball/dart
	E_LAUNCHED,//During launch
	E_ENDOFLAUNCH,//After launch
	E_SCORECALCULATED,
	E_WIN, //Win the game
	E_GAMEOVER // Gameover
};

class GameInterface;
class CameraManager;
class FSM;

class State
{
public:
	State(GameInterface* iGame, FSM& iFSM, int iId);
	virtual ~State(void);

	virtual void OnEnter(CameraManager& iCamera) = 0;
	virtual void OnExit(CameraManager& iCamera)  = 0;
	//virtual void Update(INPUTACTION iAction, CameraManager& iCamera)  = 0;
	//void AddAction(InputActionInfo infoInput);


	std::string Transition(Event);
	const int GetID() const;

protected:
	GameInterface* mGame;
	int mId;
	std::map<Event, std::string> mTransitionTable;
	FSM* mFSM;
	//InputActionInfo mInputInfo;

};


#endif //BDDSTATE_H
