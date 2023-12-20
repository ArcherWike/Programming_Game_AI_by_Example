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
	pNeighbor->GetPrintable()->Show_user(": Oh whaa This garden it's really pretty!");
}

void EnterDogoGarden::Execute(Neighbor* pNeighbor)
{
	//	if (!pNeighbor->AtDogoArea())
	//	{
	//		pNeighbor->GetPrintable()->Show_user(": oh! Dog what have you got in the garden?");
	//		//send a delayed message myself so that I know when to take the potato are cooked
	//		Dispatch->myDispatchMessage(2,                  //time delay
	//			pNeighbor->ID(),           //sender ID
	//			ent_Dogo,           //receiver ID
	//			Msg_StrangerComing,        //msg
	//			0);
	//		pNeighbor->SetAtDogoArea(true);
	//
	//	}
	//	pNeighbor->GetPrintable()->Show_user(": *looking at the garden*");
	//}
}

void EnterDogoGarden::Exit(Neighbor* pNeighbor)
{
	pNeighbor->GetPrintable()->Show_user(": Uhh.. *jump back*");
	pNeighbor->GetPrintable()->Show_user(": I'm running away from here aaaa...");
}

bool EnterDogoGarden::OnMessage(Neighbor* pNeighbor, const Telegram& msg)
{
	SetTextColor(160 | 224 | 160 | 224);
	switch (msg.Msg)
	{
	case Msg_DogoIsDangerous:
	{
		std::cout << "\nMessage received by " << GetNameOfEntity(pNeighbor->ID()) <<
			" at time: " << Clock->GetCurrentTime();
		SetTextColor(0 | 0 | 0 | 0);
		std::cout << "\n";
		pNeighbor->GetPrintable()->Show_user(": Aaa! I'm scared of that dog! Aaa!");

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
	pNeighbor->GetPrintable()->Show_user(": it's time to go");
}

void EscapesHome::Execute(Neighbor* pNeighbor)
{
	int random_num = rand() % 10;
	switch (random_num)
	{
	case 0:
		pNeighbor->GetPrintable()->Show_user(": Ugh It's close...");
		pNeighbor->GetFSM()->ChangeState(WatchTV::Instance());
		break;
	case 1:
		pNeighbor->GetPrintable()->Show_user(": Aa..");
	case 2:
		pNeighbor->GetPrintable()->Show_user(": Am I sure I'm running in the right direction?? ");
		break;
	default:
		pNeighbor->GetPrintable()->Show_user(": aaA!");
		break;
	}
	pNeighbor->GetPrintable()->Show_user(": I'm run away!!");
}

void EscapesHome::Exit(Neighbor* pNeighbor)
{
	pNeighbor->GetPrintable()->Show_user(": uff! I can see my lovely home");
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
	int random_num = rand() % 10;
	switch (random_num)
	{
	case 4:
		//std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": wylacze tv ..";
		pNeighbor->GetFSM()->ChangeState(EnterDogoGarden::Instance());
		break;
	default:
		//std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": zmienia kanal";
		break;
	}
}

void WatchTV::Exit(Neighbor* pNeighbor)
{
	pNeighbor->GetPrintable()->Show_user(": I'm going for a walk");
}

bool WatchTV::OnMessage(Neighbor* pNeighbor, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}