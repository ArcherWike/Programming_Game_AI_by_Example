#include "Neighbor.h"

bool Neighbor::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Neighbor::Update()
{
	m_pStateMachine->Update();

	//if (m_pCurrentState) //check--
	//{
	//	m_pCurrentState->Execute(this);
	//}

}