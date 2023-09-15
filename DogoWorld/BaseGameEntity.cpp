#include "BaseGameEntity.h"
#include <cassert>

int BaseGameEntity::m_iNextValidID = 0;

//----------------------------- SetID -----------------------------------------
//
//  this must be called within each constructor to make sure the ID is set
//  correctly.
//-----------------------------------------------------------------------------
void BaseGameEntity::SetID(int val)
{
    //make sure the val is equal to or greater than the next available ID
    assert((val >= m_iNextValidID) && "<BaseGameEntity::SetID>: invalid ID");

    m_ID = val;

    m_iNextValidID = m_ID + 1;
}