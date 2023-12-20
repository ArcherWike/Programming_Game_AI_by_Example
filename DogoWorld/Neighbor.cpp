#include "Neighbor.h"

bool Neighbor::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Neighbor::Update()
{
	
	SetTextColor(0 | 14 | 0 | 14);
	//SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | 112 | FOREGROUND_BLUE);
	m_pStateMachine->Update();
}