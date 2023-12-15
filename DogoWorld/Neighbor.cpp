#include "Neighbor.h"

bool Neighbor::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Neighbor::Update()
{
	SetTextColor(0 | 14 | 0 | 14);
	m_pStateMachine->Update();
}