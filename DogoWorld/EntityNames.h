#pragma once
#ifndef NAMES_H
#define NAMES_H

#include <string>

enum
{
	ent_Dogo,
	ent_Neighbor
};

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