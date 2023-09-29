#pragma once

//-------------------------------------------------------
//
//		Name: Dogo
//
//--------------------------------------------------------
#include <cassert>
#include <string>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "DogoOwnedStates.h"
#include "StateMachine.h"

//check--
//class State;

struct Telegram;

const int MaxPotato = 30;

const int HungryThreshold = 5;
const int ComfortLevel = 5;
const int TirednessThreshold = 5; //comment check--


class Dogo : public BaseGameEntity
{
private:
	//an instance of the state machine class
	StateMachine<Dogo>* m_pStateMachine;
	location_type m_Location;

	/// Dogo stats and items
	int m_iPotatoAmount;
	int m_iPotatoInHome;
	int m_iThirst;
	int m_iHungry;
	int m_iFun;
	int m_iFatigue;
	bool m_iCooking;

public:

	Dogo(int id) :m_Location(bed),
		m_iPotatoAmount(0),
		m_iPotatoInHome(0),
		m_iThirst(0),
		m_iHungry(10),
		m_iFatigue(0),
		m_iFun(0),
		m_iCooking(false),
		BaseGameEntity(id)
	{
		//set up state machine
		m_pStateMachine = new StateMachine<Dogo>(this);

		m_pStateMachine->SetCurrentState(GoBedAndSleep::Instance());

		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	}
	//check-- nie byllo nic w nawiasach

	~Dogo() { delete m_pStateMachine; }

	void Update();

	virtual bool  HandleMessage(const Telegram& msg);
	
	StateMachine<Dogo>* GetFSM()const { return m_pStateMachine; }


    //-------------------------------------------------------------
	location_type Location()const { return m_Location; }
	void ChangeLocation(const location_type loc) { m_Location = loc; }

	int PotatoAmount()const { return m_iPotatoAmount; } //check-- why in header file :eye:    const :eyye:
	void SetPotatoAmount(const int val) { m_iPotatoAmount = val; } //what
	void AddToPotatoAmount(const int val);
	bool PocketFull()const { return m_iPotatoAmount >= MaxPotato; }

	bool Fatigued()const;
	void DecreaseFatigue() { m_iFatigue -= 1; }
	void IncreaseFatigue() { m_iFatigue += 1; }

	int Wealth()const { return m_iPotatoInHome; }
	int SetWealth(const int val) { m_iPotatoInHome = val; }
	void AddToWealth(const int val);

	bool Hungry()const { return m_iHungry >= HungryThreshold; };
	void DecreaseHungry() { m_iHungry -= 5; }
	void IncreaseHungry() { m_iHungry += 1; }

	bool Cooking()const { return m_iCooking; }
	void SetCooking(bool val) { m_iCooking = val; }

	bool Thirsty()const;
	void BuyAndDrinkWater() { m_iThirst = 0; m_iPotatoInHome -= 2; }

};