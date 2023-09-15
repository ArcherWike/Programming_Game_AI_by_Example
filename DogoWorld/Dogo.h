#pragma once

//-------------------------------------------------------
//
//		Name: Dogo
//
//--------------------------------------------------------
#include <cassert>

#include "BaseGameEntity.h"
#include "Locations.h"

//check--
class State;


const int MaxPotato = 5;

const int ComfortLevel = 5;
const int TirednessThreshold = 5; //comment check--

class Dogo : public BaseGameEntity
{
private:
	State* m_pCurrentState;
	location_type m_Location;

	/// Dogo stats and items
	int m_iPotatoAmount;
	int m_iPotatoInHome;
	int m_iThirst;
	int m_iFun;
	int m_iFatigue;

public:
	Dogo(int id);

	void Update();

	void ChangeState(State* new_state);


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

	bool Thirsty()const;
	void BuyAndDrinkWater() { m_iThirst = 0; m_iPotatoInHome -= 2; }

};