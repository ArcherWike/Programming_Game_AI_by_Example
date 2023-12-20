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
		std::cout << ": Hau hau... Walk to the garden";

		pDogo->ChangeLocation(garden);
	}
}

void EnterGardenAndDig::Execute(Dogo* pDogo)
{
	//Dogo dig until it is carring in excess of MaxPotato.

	pDogo->IncreaseFatigue();
	pDogo->IncreaseHungry();
	
	int random_num = rand() % 5;
	pDogo->AddToPotatoAmount(random_num);
	switch (random_num)
	{
	case 0:
		pDogo->GetPrintable()->Show_user(": Failed to dig up anything this time :(");
		break;
	case 1:
		pDogo->GetPrintable()->Show_user(": Digging up a potato...");
		break;
	case 2:
		pDogo->GetPrintable()->Show_user(": Digging up a potato..");
		break;
	case 3:
		pDogo->GetPrintable()->Show_user(": Digging up lots of potato");
		break;
	default:
		pDogo->GetPrintable()->Show_user(": Digging up a potato.");
		break;
	}


	//back to home if true
	if (pDogo->Hungry() && pDogo->GetFSM()->PreviousState() != VisitHomeAndDepositPotato::Instance())
	{
		pDogo->GetFSM()->ChangeState(VisitHomeAndDepositPotato::Instance());
		pDogo->GetPrintable()->Show_user(": I'm hungry :saddge:");
	}
	if (pDogo->PocketFull())
	{
		pDogo->GetPrintable()->Show_user(": My pockets is full of sweet potato");
		pDogo->GetFSM()->ChangeState(VisitHomeAndDepositPotato::Instance());
	}
}

void EnterGardenAndDig::Exit(Dogo* pDogo)
{
	pDogo->GetPrintable()->Show_user(": Ah I'm leaving garden!");
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
			SetTextColor(0 | 0 | 0 | 0);
			std::cout << "\n";

			pDogo->SetBarking(false);
			pDogo->GetFSM()->ChangeState(BarkAtStranger::Instance());
		
		}
		return true;
	}

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
	pDogo->GetPrintable()->Show_user(": Someone is there! :sus:");
	pDogo->GetPrintable()->Show_user(": I need to check it out!");
}

void BarkAtStranger::Execute(Dogo* pDogo)
{
	
		int random_num = rand() % 10;
		switch (random_num)
		{
		case 0:
			pDogo->GetPrintable()->Show_user(": Woof woof!!!");
			break;
		case 2:
			pDogo->GetPrintable()->Show_user(": I'm danger!!! Woof woof!");
			break;
		case 3:
			pDogo->GetPrintable()->Show_user(": That's private area! What are you doing here??! I'll call the police! WOOF! woof!");
			break;
		case 7:
			if (!pDogo->Barking())
			{
				//send a message to stranger neighbour that
							// he should be feared if he want stay alive
				Dispatch->myDispatchMessage(1, //time delay
					pDogo->ID(),				//sender ID
					ent_Neighbor,				//receiver ID
					Msg_DogoIsDangerous,        //msg
					0);
				pDogo->SetBarking(true);


			}
			pDogo->GetFSM()->ChangeState(pDogo->GetFSM()->PreviousState());
		default:
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
		pDogo->GetPrintable()->Show_user(": Going to my lovely home! Yes sireee");

		pDogo->ChangeLocation(home);
	}
}

void VisitHomeAndDepositPotato::Execute(Dogo* pDogo)
{
	//deposit potato
	pDogo->AddToWealth(pDogo->PotatoAmount());

	pDogo->SetPotatoAmount(0);
	pDogo->GetPrintable()->Show_user(": Depositing potatoes. Total savings now:");
	std::cout << " " << pDogo->Wealth();

	if (pDogo->Hungry())
	{
		if (pDogo->Wealth() > 3)
		{
			pDogo->GetPrintable()->Show_user(": I'm hungry, I'll check if I have enough food. Woof!");
			pDogo->SetCooking(false);
			pDogo->GetFSM()->ChangeState(CookPotatoes::Instance());
		}
		else
		{
			pDogo->GetPrintable()->Show_user(": Not enought potatoes :C");
			pDogo->GetFSM()->ChangeState(EnterGardenAndDig::Instance());
		}
	}
	//wealthy enough to have a well earned rest?
	else if (pDogo->Wealth() >= ComfortLevel)
	{
		pDogo->GetPrintable()->Show_user(": WooHoo Hau Hau! Rich enough for now. Going to sleep");

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
	SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | 112 | FOREGROUND_BLUE);
	switch (msg.Msg)
	{
	case Msg_StrangerComing:
	{
		std::cout << "\nMessage received by " << GetNameOfEntity(pDogo->ID()) <<
			" at time: " << Clock->GetCurrentTime();
		SetTextColor(0 | 0 | 0 | 0);
		std::cout << "\n";

		pDogo->SetBarking(false);
		pDogo->GetFSM()->ChangeState(BarkAtStranger::Instance());

	}
	return true;
	}

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
		pDogo->GetPrintable()->Show_user(": Putting the potato in the oven");

		//send a delayed message myself so that I know when to take the potato are cooked
		Dispatch->myDispatchMessage(4,                  //time delay
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
		pDogo->GetPrintable()->Show_user(": still waiting.");
		break;
	case 1:
		pDogo->GetPrintable()->Show_user(": still waiting..");
		break;
	case 2:
		pDogo->GetPrintable()->Show_user(": still waiting...");
		break;
	default:
		break;
	}
}

void CookPotatoes::Exit(Dogo* pDogo)
{
	pDogo->SetCooking(false);
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
			SetTextColor(0 | 0 | 0 | 0);
			std::cout << "\n";
			

			pDogo->GetPrintable()->Show_user(": I'm coming!");

			pDogo->GetFSM()->ChangeState(EatPotatoes::Instance());
			pDogo->SetCooking(false);
		}
		case Msg_StrangerComing:
		{
			std::cout << "\nMessage received by " << GetNameOfEntity(pDogo->ID()) <<
				" at time: " << Clock->GetCurrentTime();
			SetTextColor(0 | 0 | 0 | 0);
			std::cout << "\n";

			pDogo->SetBarking(false);
			pDogo->GetFSM()->ChangeState(BarkAtStranger::Instance());

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
		pDogo->GetPrintable()->Show_user(": Going to my lovely home! Yes sireee");

		pDogo->ChangeLocation(home);
	}
	pDogo->GetPrintable()->Show_user(": Smells Reaaal goood! :O");
}

void EatPotatoes::Execute(Dogo* pDogo)
{

	if (!pDogo->Hungry())
	{
		pDogo->GetPrintable()->Show_user(": After such good food, one should relax!");
		pDogo->GetFSM()->ChangeState(GoBedAndSleep::Instance());
	}
	else 
	{
		int random_num = rand() % 5;
		switch (random_num)
		{
		case 0:
			pDogo->GetPrintable()->Show_user(": Am am am...");
			break;
		case 1:
			pDogo->GetPrintable()->Show_user(": Am..");
			break;
		case 2:
			pDogo->GetPrintable()->Show_user(": Oh Tastes real good!");
			break;
		default:
			pDogo->GetPrintable()->Show_user(": am am..");
			break;
		}
		pDogo->DecreaseHungry();
	}
}

void EatPotatoes::Exit(Dogo* pDogo)
{
	pDogo->GetPrintable()->Show_user(": Leave kitchen");
}
bool EatPotatoes::OnMessage(Dogo* pDogo, const Telegram& msg)
{
	SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | 112 | FOREGROUND_BLUE);
	switch (msg.Msg)
	{
	case Msg_StrangerComing:
	{
		std::cout << "\nMessage received by " << GetNameOfEntity(pDogo->ID()) <<
			" at time: " << Clock->GetCurrentTime();
		SetTextColor(0 | 0 | 0 | 0);
		std::cout << "\n";

		pDogo->SetBarking(false);
		pDogo->GetFSM()->ChangeState(BarkAtStranger::Instance());

	}
	return true;
	}

	//send msg to global message handler
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
		pDogo->GetPrintable()->Show_user(": I need rest! Go to the bed.");

		pDogo->ChangeLocation(bed);
	}
}

void GoBedAndSleep::Execute(Dogo* pDogo)
{
	//if dogo is not fatigued start to dig for potato again.
	if (!pDogo->Fatigued())
	{
		pDogo->GetPrintable()->Show_user(": What a God darn fantastic nap! Time to find more potato!");

		pDogo->GetFSM()->ChangeState(EnterGardenAndDig::Instance());
	}
	else
	{
	//sleep
	pDogo->DecreaseFatigue();


	int random_num = rand() % 3;
	switch (random_num)
	{
	case 0:
		pDogo->GetPrintable()->Show_user(": ZZzzz...");
		break;
	case 1:
		pDogo->GetPrintable()->Show_user(": ZZzzz. Zzz..");
		break;
	case 2:
		pDogo->GetPrintable()->Show_user(": zZz.");
		break;
	}
	

	}
}

void GoBedAndSleep::Exit(Dogo* pDogo)
{
	pDogo->GetPrintable()->Show_user(": Leaving bed");
}

bool GoBedAndSleep::OnMessage(Dogo* pDogo, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}