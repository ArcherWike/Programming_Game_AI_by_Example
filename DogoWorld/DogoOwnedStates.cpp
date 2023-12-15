#include "DogoOwnedStates.h"
#include "State.h"
#include "Dogo.h"
#include "Locations.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

#define FOREGROUND_GRay 0xAAAA // text color is intensified.


//--------------------------------------methods for EnterGardenAndDig

EnterGardenAndDig* EnterGardenAndDig::Instance() //check--
{
	static EnterGardenAndDig instance;

	return &instance;
}

void EnterGardenAndDig::Enter(Dogo* pDogo)
{
	if (pDogo->Location() != garden)
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Hau hau... Walk to the garden";

		pDogo->ChangeLocation(garden);
	}
}

void EnterGardenAndDig::Execute(Dogo* pDogo)
{
	//Dogo dig until it is carring in excess of MaxPotato.

	pDogo->IncreaseFatigue();
	pDogo->IncreaseHungry();
	
	int random_num = rand() % 10;
	pDogo->AddToPotatoAmount(random_num);
	switch (random_num)
	{
	case 0:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Failed to dig up anything this time";
		break;
	case 5:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Digging up a potato...";
		break;
	case 7:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Digging up a potato..";
		break;
	case 9:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Digging up lots of potato";
		break;
	default:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Digging up a potato.";
		break;
	}


	//back to home if true
	if (pDogo->Hungry() && pDogo->GetFSM()->PreviousState() != VisitHomeAndDepositPotato::Instance())
	{
		pDogo->GetFSM()->ChangeState(VisitHomeAndDepositPotato::Instance());
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": I'm hungry :saddge:";
	}
	if (pDogo->PocketFull())
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": My pockets is full of sweet potato";
		pDogo->GetFSM()->ChangeState(VisitHomeAndDepositPotato::Instance());
	}
}

void EnterGardenAndDig::Exit(Dogo* pDogo)
{
	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Ah I'm leaving garden!";
}


bool EnterGardenAndDig::OnMessage(Dogo* pDogo, const Telegram& msg)
{
	SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | 112 | FOREGROUND_BLUE);
	switch (msg.Msg)
	{
		case Msg_StrangerComing:
		{
			std::cout << "\nMessage received by " << GetNameOfEntity(pDogo->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			pDogo->GetFSM()->ChangeState(BarkAtStranger::Instance());
		
		}
		return true;
	}
	return false;

	//send msg to global message handler
	return false;
}

//--------------------------------------methods for BarkAtStranger
BarkAtStranger* BarkAtStranger::Instance() //check--
{
	static BarkAtStranger instance;

	return &instance;
}

void BarkAtStranger::Enter(Dogo* pDogo)
{
	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": o nie kto to na posesjii!!";
	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Juz tam biegneeem!!!";
}

void BarkAtStranger::Execute(Dogo* pDogo)
{
	int random_num = rand() % 5;
	switch (random_num)
	{
	case 0:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Woof woof!!!";
		break;
	case 1:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": woof...!!!";
		break;
	case 2:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": " << "I'm danger!!! Woof woof!";

		//send a message to stranger neighbour that
		// he should be feared if he want stay alive
		Dispatch->myDispatchMessage(-1, //time delay
			pDogo->ID(),				//sender ID
			ent_Neighbor,				//receiver ID
			Msg_DogoIsDangerous,        //msg
			0);

		pDogo->GetFSM()->PreviousState();
		break;
	default:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Woof!";
		break;
	}
}

void BarkAtStranger::Exit(Dogo* pDogo)
{

}

bool BarkAtStranger::OnMessage(Dogo* pDogo, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//----------------------------------------methods for VisitHomeAndDepositPotato

VisitHomeAndDepositPotato* VisitHomeAndDepositPotato::Instance()
{
	static VisitHomeAndDepositPotato instance;
	return &instance;
}

void VisitHomeAndDepositPotato::Enter(Dogo* pDogo)
{
	//on entry the dogo makes sure he is located at home
	if (pDogo->Location() != home)							//check-- is possible
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Going to my lovely home! Yes sireee";

		pDogo->ChangeLocation(home);
	}
}

void VisitHomeAndDepositPotato::Execute(Dogo* pDogo)
{
	//deposit potato
	pDogo->AddToWealth(pDogo->PotatoAmount());

	pDogo->SetPotatoAmount(0);

	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Depositing potatoes. Total savings now: " << pDogo->Wealth();

	if (pDogo->Hungry())
	{
		if (pDogo->Wealth() > 3)
		{
			std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": I'm hungry, I'll check if I have enough food. Woof test";

			pDogo->GetFSM()->ChangeState(CookPotatoes::Instance());
		}
		else
		{
			std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Not enought potatoes :C";
			pDogo->GetFSM()->ChangeState(EnterGardenAndDig::Instance());
		}
	}
	//wealthy enough to have a well earned rest?
	else if (pDogo->Wealth() >= ComfortLevel)
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ":WooHoo Hau Hau! Rich enough for now. Going to sleep";

		pDogo->GetFSM()->ChangeState(GoBedAndSleep::Instance());
	}
	//get more potato
	else
	{
		pDogo->GetFSM()->ChangeState(EnterGardenAndDig::Instance());
	}
}

void VisitHomeAndDepositPotato::Exit(Dogo* pDogo)
{
	//std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Leaving home";
}

bool VisitHomeAndDepositPotato::OnMessage(Dogo* pDogo, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}
//----------------------------------------methods for CookPotatoes

CookPotatoes* CookPotatoes::Instance()
{
	static CookPotatoes instance;

	return &instance;
}

void CookPotatoes::Enter(Dogo* pDogo)
{

	if (!pDogo->Cooking())
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Putting the potato in the oven";

		//send a delayed message myself so that I know when to take the potato are cooked
		Dispatch->myDispatchMessage(15,                  //time delay
			pDogo->ID(),           //sender ID
			ent_Dogo,           //receiver ID
			Msg_PotatoReady,        //msg
			0);
		pDogo->SetCooking(true);
	}
	
}

void CookPotatoes::Execute(Dogo* pDogo)
{
	int random_num = rand() %3;
	switch (random_num)
	{
	case 0:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": still waiting.";
		break;
	case 1:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": still waiting..";
		break;
	case 2:
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": still waiting...";
		break;
	default:
		break;
	}
}

void CookPotatoes::Exit(Dogo* pDogo)
{

}

bool CookPotatoes::OnMessage(Dogo* pDogo, const Telegram& msg)
{
	SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | 112 | FOREGROUND_BLUE);
	switch (msg.Msg)
	{
		case Msg_PotatoReady:
		{
			std::cout << "\nMessage received by " << GetNameOfEntity(pDogo->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": I'm coming!";

			pDogo->GetFSM()->ChangeState(EatPotatoes::Instance());
			pDogo->SetCooking(false);
		}
		return true;
	}
	return false;
}
//----------------------------------------methods for EatPotatoes

EatPotatoes* EatPotatoes::Instance()
{
	static EatPotatoes instance;

	return &instance;
}

void EatPotatoes::Enter(Dogo* pDogo)
{
	if (pDogo->Location() != home)							//check-- is possible
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Going to my lovely home! Yes sireee";

		pDogo->ChangeLocation(home);
	}
	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": " << "Smells Reaaal goood! :O";
}

void EatPotatoes::Execute(Dogo* pDogo)
{

	if (!pDogo->Hungry())
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": " << "After such good food, one should relax!";
		pDogo->GetFSM()->ChangeState(GoBedAndSleep::Instance());
	}
	else 
	{
		int random_num = rand() % 5;
		switch (random_num)
		{
		case 0:
			std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Am am am...";
			break;
		case 1:
			std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": am..";
			break;
		case 2:
			std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": " << "Oh Tastes real good!";
			break;
		default:
			std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": am am..";
			break;
		}
		pDogo->DecreaseHungry();
	}
}

void EatPotatoes::Exit(Dogo* pDogo)
{
	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": " << "Leave kitchen";
}
bool EatPotatoes::OnMessage(Dogo* pDogo, const Telegram& msg)
{
	return false;
}

//----------------------------------------methods for GoBedAndSleep

GoBedAndSleep* GoBedAndSleep::Instance()
{
	static GoBedAndSleep instance;

	return &instance;
}

void GoBedAndSleep::Enter(Dogo* pDogo)
{
	if (pDogo->Location() != bed)
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": I need rest! Go to the bed.";

		pDogo->ChangeLocation(bed);
	}
}

void GoBedAndSleep::Execute(Dogo* pDogo)
{
	//if dogo is not fatigued start to dig for potato again.
	if (!pDogo->Fatigued())
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": What a God darn fantastic nap! Time to find more potato!";

		pDogo->GetFSM()->ChangeState(EnterGardenAndDig::Instance());
	}
	else
	{
	//sleep
	pDogo->DecreaseFatigue();

	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": ZZzzz...";
	}
}

void GoBedAndSleep::Exit(Dogo* pDogo)
{
	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Leaving bed";
}

bool GoBedAndSleep::OnMessage(Dogo* pDogo, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}