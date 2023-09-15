#pragma once
#ifndef DOGO_OWNED_STATES_H
#define DOGO_OWNED_STATES_H

//------------------------------------------------------------------------
//
//  Name:   DogoOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Dogo class
//
//------------------------------------------------------------------------
#include "State.h"

class Dogo; //check-- #include ??


//------------------------------------------------------------------------
//
//  In this state the Dogo will walk to the garden and pick up a potato
//  for lunch. If Dogo already has enough potato. it'll change state
//  to \. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class EnterGardenAndDig : public State
{
private:
	EnterGardenAndDig() {}

	////copy ctor and assignment should be private				//check--
	//EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
	//EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);

	EnterGardenAndDig(const EnterGardenAndDig&);
	EnterGardenAndDig& operator=(const EnterGardenAndDig&);

public:
	//singleton

	static EnterGardenAndDig* Instance(); //chceck--
	virtual void Enter(Dogo* dogo);
	virtual void Execute(Dogo* dogo);
	virtual void Exit(Dogo* dogo);
};

//------------------------------------------------------------------------
//
//  Entity will go to the kitchen and deposit any potato he is carrying. If Dogo
//  is subsequently wealthy enough he'll go sleep, otherwise he'll
//  keep going to get more potato
//------------------------------------------------------------------------

class VisitHomeAndDepositPotato : public State
{
private:
	VisitHomeAndDepositPotato() {}

	VisitHomeAndDepositPotato(const VisitHomeAndDepositPotato&);
	VisitHomeAndDepositPotato& operator=(const VisitHomeAndDepositPotato&);

public:
	static VisitHomeAndDepositPotato* Instance();
	virtual void Enter(Dogo* dogo);
	virtual void Execute(Dogo* dogo);
	virtual void Exit(Dogo* dogo);
};

//------------------------------------------------------------------------
//
//  Dogo will go sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoBedAndSleep : public State
{
private:

	GoBedAndSleep() {}

	//copy ctor and assignment should be private
	GoBedAndSleep(const GoBedAndSleep&);
	GoBedAndSleep& operator=(const GoBedAndSleep&);

public:

	//this is a singleton
	static GoBedAndSleep* Instance();

	virtual void Enter(Dogo* dogo);

	virtual void Execute(Dogo* miner);

	virtual void Exit(Dogo* miner);
};

#endif