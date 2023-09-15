#pragma once ////////////////////////////////////////sus
#ifndef ENTITY_H   //check--
#define ENTITY_H

class BaseGameEntity
{
private:
	//every entity has a unique identifying number
	int m_ID;
	
	static int m_iNextValidID;
	
	void SetID(int val);
public:
	BaseGameEntity(int id)
	{
		SetID(id);
	}
	virtual ~BaseGameEntity() {}
	//all entities must implement an update function
	virtual void Update() = 0;
	int ID()const { return m_ID; }
};
#endif