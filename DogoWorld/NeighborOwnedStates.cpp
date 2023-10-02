#include "NeighborOwnedStates.h"
#include "State.h"
#include "Neighbor.h"
#include "Locations.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>



//--------------------------------------methods for EnterDogoGarden
EnterDogoGarden* EnterDogoGarden::Instance()
{
	static EnterDogoGarden instance;

	return &instance;
}

void EnterDogoGarden::Enter(Neighbor* pNeighbor)
{

}

void EnterDogoGarden::Execute(Neighbor* pNeighbor)
{

}

void EnterDogoGarden::Exit(Neighbor* pNeighbor)
{

}

bool EnterDogoGarden::OnMessage(Neighbor* pNeighbor, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}
//--------------------------------------methods for EscapesHome
EscapesHome* EscapesHome::Instance()
{
	static EscapesHome instance;

	return &instance;
}

void EscapesHome::Enter(Neighbor* pNeighbor)
{

}

void EscapesHome::Execute(Neighbor* pNeighbor)
{

}

void EscapesHome::Exit(Neighbor* pNeighbor)
{

}

bool EscapesHome::OnMessage(Neighbor* pNeighbor, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}
//--------------------------------------methods for WatchTV
WatchTV* WatchTV::Instance()
{
	static WatchTV instance;

	return &instance;
}

void WatchTV::Enter(Neighbor* pNeighbor)
{

}

void WatchTV::Execute(Neighbor* pNeighbor)
{

}

void WatchTV::Exit(Neighbor* pNeighbor)
{

}

bool WatchTV::OnMessage(Neighbor* pNeighbor, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}