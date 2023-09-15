#include "Dogo.h"
#include "DogoOwnedStates.h"

Dogo::Dogo(int id) :BaseGameEntity(id),
m_Location(bed),
m_iPotatoAmount(0),
m_iPotatoInHome(0),
m_iThirst(0),
m_iFatigue(0),
m_iFun(0),
m_pCurrentState(GoBedAndSleep::Instance())
{}
//check--

//--------------------------- ChangeState -------------------------------------
//-----------------------------------------------------------------------------

void  Dogo::ChangeState(State* pNewState)
{
	//make sure both states are both valid before attempting to 
   //call their methods
	assert(m_pCurrentState && pNewState);

	//call the exit method of the existing state
	m_pCurrentState->Exit(this);

	//change state to the new state
	m_pCurrentState = pNewState;

	//call the entry method of the new state
	m_pCurrentState->Enter(this);
}

//------------------------------------------------------------------------------
// Dogo::

void Dogo::AddToPotatoAmount(const int val)
{
	m_iPotatoAmount += val;
	
	if (m_iPotatoAmount < 0)
	{
		m_iPotatoAmount = 0;
	}
}

void Dogo::AddToWealth(const int val)
{
	m_iPotatoInHome += val;

	if (m_iPotatoInHome < 0)
	{
		m_iPotatoAmount = 0;
	}
}

bool Dogo::Fatigued()const //chceck--
{
	if (m_iFatigue > TirednessThreshold)
	{
		return true;
	}
	return false;
}

void Dogo::Update()
{
	m_iThirst += 1;

	if (m_pCurrentState) //check--
	{
		m_pCurrentState->Execute(this);
	}

}