#pragma once
#ifndef NAMES_H
#define NAMES_H

#include <string>

enum
{
	ent_Dogo
};

inline std::string GetNameOfEntity(int n)
{
	switch (n)
	{
	case ent_Dogo:
		return "Dogo";

	default:
		return "UNKNOWN!";
	}
}
#endif