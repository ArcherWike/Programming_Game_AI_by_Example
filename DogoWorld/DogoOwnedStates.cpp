#include "DogoOwnedStates.h"
#include "State.h"
#include "Dogo.h"
#include "Locations.h"
#include "EntityNames.h"

#include <iostream>


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
	pDogo->AddToPotatoAmount(1);
	
	pDogo->IncreaseFatigue();

	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Digging up a potato";

	if (pDogo->PocketFull())
	{
		pDogo->ChangeState(VisitHomeAndDepositPotato::Instance());
	}
	
}

void EnterGardenAndDig::Exit(Dogo* pDogo)
{
	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Ah I'm leaving garden with pockets full of sweet potato!";
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

	//wealthy enough to have a well earned rest?
	if (pDogo->Wealth() >= ComfortLevel)
	{
		std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ":WooHoo Hau Hau! Rich enough for now. Going to sleep";

		pDogo->ChangeState(GoBedAndSleep::Instance());
	}
	//get more potato
	else
	{
		pDogo->ChangeState(EnterGardenAndDig::Instance());
	}
}

void VisitHomeAndDepositPotato::Exit(Dogo* pDogo)
{
	std::cout << "\n" << GetNameOfEntity(pDogo->ID()) << ": Leaving home";
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

		pDogo->ChangeState(EnterGardenAndDig::Instance());
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