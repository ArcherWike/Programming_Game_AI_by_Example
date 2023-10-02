#pragma once

//-------------------------------------------------------
//
//		Name: Neighbor
//
//--------------------------------------------------------
#include <cassert>
#include <string>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "NeighborOwnedStates.h"
#include "StateMachine.h"
struct Telegram;

class Neighbor : public BaseGameEntity
{
private: 
	StateMachine<Neighbor>* m_pStateMachine;
	   location_type m_Location;
public:
	Neighbor(int id): m_Location(garden),
		BaseGameEntity(id)
{
	//set up state machine
	m_pStateMachine = new StateMachine<Neighbor>(this);

	m_pStateMachine->SetCurrentState(EnterDogoGarden::Instance());
}
	~Neighbor() { delete m_pStateMachine; }
	void Update();
	virtual bool  HandleMessage(const Telegram& msg);
	StateMachine<Neighbor>* GetFSM()const { return m_pStateMachine; }

	//-------------------------------------------------------------
	location_type Location()const { return m_Location; }
	void ChangeLocation(const location_type loc) { m_Location = loc; }
};