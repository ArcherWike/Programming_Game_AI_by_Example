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
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": o Piesel co tam masz w ogrodku";
		//send a delayed message myself so that I know when to take the potato are cooked
		Dispatch->myDispatchMessage(15,                  //time delay
			pNeighbor->ID(),           //sender ID
			ent_Dogo,           //receiver ID
			Msg_StrangerComing,        //msg
			0);
		pNeighbor->SetAtDogoArea(true);

	}
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": *zaglada na ogrod*";
}

void EnterDogoGarden::Exit(Neighbor* pNeighbor)
{
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": aaaa..";
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": *skok w tyl*";
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": uciekam stad aaaa...";
}

bool EnterDogoGarden::OnMessage(Neighbor* pNeighbor, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_DogoIsDangerous:
	{
		std::cout << "\nMessage received by " << GetNameOfEntity(pNeighbor->ID(),false) <<
			" at time: " << Clock->GetCurrentTime();

		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": aaa boje sie tego piesla!! aaaaa!";

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
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": pora sie zwijavc";
}

void EscapesHome::Execute(Neighbor* pNeighbor)
{
	int random_num = rand() % 10;
	switch (random_num)
	{
	case 0:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": uf juz blisko...";
		pNeighbor->GetFSM()->ChangeState(WatchTV::Instance());
		break;
	case 1:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": Aa..";
	case 2:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": Czy ja napewno w dobra strone biegne?? ";
		break;
	default:
		std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": aaA!";
		break;
	}
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": aaaaaa uciekam";
}

void EscapesHome::Exit(Neighbor* pNeighbor)
{
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": o  widze dom";
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
	std::cout << "\n" << GetNameOfEntity(pNeighbor->ID()) << ": oh moj tv";
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