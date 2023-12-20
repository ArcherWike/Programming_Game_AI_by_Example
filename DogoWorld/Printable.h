#pragma once
#include "EntityNames.h"
#include <iostream>

#include "misc/ConsoleUtils.h"

#include <windows.h>


template <class entity_type>
class Printable // --check
{
public:
	Printable(entity_type* owner, int id) :m_pOwner(owner), m_OwnerID(id)
	{}

	void Show_user(std::string message)const;
private:
	//a pointer to the agent that owns this instance
	entity_type* m_pOwner;
	int m_OwnerID;

};

template<class entity_type>
inline void Printable<entity_type>::Show_user(std::string message)const
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	

	columns = columns - (columns / 2);
	std::cout << "\n";
	//SetTextColor(BACKGROUND_INTENSITY | 176 | 16 | 176);

	PrintNameOfEntity(m_OwnerID);

	int length = message.length();
	int t = 0;
	int tc_screen = (GetNameOfEntity(m_OwnerID)).length();
	SetTextColor(0 | 3 | 0 | 3);
	
	while (t < length)
	{
		if (tc_screen > columns)
		{
			tc_screen = 0;
			std::cout << "\n";
		}
		std::cout << message[t];
		t++;
		tc_screen++;
	}
	
}
