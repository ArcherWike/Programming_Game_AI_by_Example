#ifndef STATE_H
#define STATE_H
//------------------------------------------------------------------------
//
//  Name:   State.h
//
//------------------------------------------------------------------------

class Dogo;

class State
{
public:

	virtual ~State() {}

	//this will execute when the state is entered
	virtual void Enter(Dogo*) = 0;

	//this is the state's normal update function
	virtual void Execute(Dogo*) = 0;

	//this will execute when the state is exited. (My word, isn't
	//life full of surprises... ;o))
	virtual void Exit(Dogo*) = 0;

};

#endif