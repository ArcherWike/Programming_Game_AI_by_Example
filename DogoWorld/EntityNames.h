
#ifndef NAMES_H
#define NAMES_H

#include <string>
#include <windows.h>
#include <conio.h>
#include "misc/ConsoleUtils.h"
#include <iostream>

 

enum character
{
	ent_Dogo,
	ent_Neighbor
};

inline std::string PrintNameOfEntity(int n)
{
	switch (n)
	{
	case ent_Dogo:
		SetTextColor(BACKGROUND_INTENSITY | 176 | 16 | 176);
		std::cout << "Dogo";
		//if (previos_type != ent_Dogo)
		///{
		//	std::cout << "\n";
		//}
		//previos_type = ent_Dogo;

		return "Dogo";

	case ent_Neighbor:
		SetTextColor(160 | 224 | 160 | 224);
		std::cout << "Neighbor";
		//if (previos_type != ent_Neighbor)
		//{
		//	std::cout << "\n";
		//}
		//previos_type = ent_Neighbor;
		return "Neighbor";

	default:
		return "UNKNOWN!";
	}
}


inline std::string GetNameOfEntity(int n)
{
	switch (n)
	{
	case ent_Dogo:
		return "Dogo";

	case ent_Neighbor:
		return "Neighbor";

	default:
		return "UNKNOWN!";
	}

}
#endif