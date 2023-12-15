// DogoWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Locations.h"
#include "Dogo.h"
#include "Neighbor.h"
#include "EntityNames.h"
#include "EntityManager.h"
#include <windows.h>
#include "MessageDispatcher.h"
int main()
{
    srand((unsigned)time(NULL));

    //create a Dogo
    Dogo* Dog = new Dogo(ent_Dogo);
    std::cout << "\n";
    EntityMgr->RegisterEntity(Dog);

    //create the Neighbor
    Neighbor* neighbor = new Neighbor(ent_Neighbor);
    EntityMgr->RegisterEntity(neighbor); 
    
    // 
    
    //simply run the miner through a few Update calls
    for (int i = 0; i < 200; ++i)
    {
        Dog->Update();
        neighbor->Update();
        
        Dispatch->DispatchDelayedMessages();
        Sleep(4300);


    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
