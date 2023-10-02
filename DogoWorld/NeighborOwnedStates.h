#pragma once
#ifndef NEIGHBOR_OWNED_STATES_H
#define NEIGHBORNEIGHBOR_OWNED_STATES_H

//------------------------------------------------------------------------
//
//  Name:   DogoOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Dogo class
//
//------------------------------------------------------------------------
#include "State.h"

class Neighbor; //check-- #include ??
struct Telegram;

//------------------------------------------------------------------------
//
//  In this state the Neighbor will walk to the Dogo garden and looks into what dogo has in garden
//------------------------------------------------------------------------
class EnterDogoGarden : public State<Neighbor>
{
private:
	EnterDogoGarden() {}

	EnterDogoGarden(const EnterDogoGarden&);
	EnterDogoGarden& operator=(const EnterDogoGarden&);

public:
	//singleton

	static EnterDogoGarden* Instance(); //chceck--
	virtual void Enter(Neighbor* neighbor);
	virtual void Execute(Neighbor* neighbor);
	virtual void Exit(Neighbor* neighbor);
	virtual bool OnMessage(Neighbor* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  In this state the Neighbor afraid to dogo and escapes home
//------------------------------------------------------------------------
class EscapesHome : public State<Neighbor>
{
private:
	EscapesHome() {}

	EscapesHome(const EscapesHome&);
	EscapesHome& operator=(const EscapesHome&);

public:
	//singleton

	static EscapesHome* Instance(); //chceck--
	virtual void Enter(Neighbor* neighbor);
	virtual void Execute(Neighbor* neighbor);
	virtual void Exit(Neighbor* neighbor);
	virtual bool OnMessage(Neighbor* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  In this state the Neighbor watching TV
//------------------------------------------------------------------------
class WatchTV : public State<Neighbor>
{
private:
	WatchTV() {}

	WatchTV(const WatchTV&);
	WatchTV& operator=(const WatchTV&);

public:
	//singleton

	static WatchTV* Instance(); //chceck--
	virtual void Enter(Neighbor* neighbor);
	virtual void Execute(Neighbor* neighbor);
	virtual void Exit(Neighbor* neighbor);
	virtual bool OnMessage(Neighbor* agent, const Telegram& msg);
};

#endif