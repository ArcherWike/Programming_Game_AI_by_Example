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
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": Oh whaa This garden it's really pretty!";
}

void EnterDogoGarden::Execute(Neighbor* pNeighbor)
{
	if (!pNeighbor->AtDogoArea())
	{
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": oh! Dog what have you got in the garden?";
		//send a delayed message myself so that I know when to take the potato are cooked
		Dispatch->myDispatchMessage(15,                  //time delay
			pNeighbor->ID(),           //sender ID
			ent_Dogo,           //receiver ID
			Msg_StrangerComing,        //msg
			0);
		pNeighbor->SetAtDogoArea(true);

	}
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": *looking at the garden*";
}

void EnterDogoGarden::Exit(Neighbor* pNeighbor)
{
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": aaaa..";
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": *jump back*";
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": I'm running away from here uh aaaa...";
}

bool EnterDogoGarden::OnMessage(Neighbor* pNeighbor, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_DogoIsDangerous:
	{
		std::cout << "\nMessage received by " << GetNameOfEntity(pNeighbor->ID()) <<
			" at time: " << Clock->GetCurrentTime();

		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": aaa I'm scared of that dog! aaaaa!";

		pNeighbor->GetFSM()->ChangeState(EscapesHome::Instance());
	}
	return true;
	}
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
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": it's time to go";
}

void EscapesHome::Execute(Neighbor* pNeighbor)
{
	int random_num = rand() % 10;
	switch (random_num)
	{
	case 0:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": ugh It's close...";
		pNeighbor->GetFSM()->ChangeState(WatchTV::Instance());
		break;
	case 1:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": Aa..";
	case 2:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": Am I sure I'm running in the right direction?? ";
		break;
	default:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": aaA!";
		break;
	}
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": aaaaaa I'm run away";
}

void EscapesHome::Exit(Neighbor* pNeighbor)
{
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": uff! I can see my lovely home";
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
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": zobaczmy co ciekawgo leci";
}

void WatchTV::Execute(Neighbor* pNeighbor)
{
	int random_num = rand() % 5;
	switch (random_num)
	{
	case 0:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": wylacze tv ..";
		pNeighbor->GetFSM()->ChangeState(EnterDogoGarden::Instance());
		break;
	default:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": zmienia kanal";
		break;
	}
}

void WatchTV::Exit(Neighbor* pNeighbor)
{
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": ide sie przejsc.";
}

bool WatchTV::OnMessage(Neighbor* pNeighbor, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}