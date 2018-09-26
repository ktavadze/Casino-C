/***********************************************************
* Name: Konstantine Tavadze                                *
* Project: Casino - Milestone 2                            *
* Class: OPL                                               *
* Date: 9/25/18                                            *
***********************************************************/
#include "pch.h"
#include "Tournament.h"

using namespace std;

int main()
{
    Tournament tournament;

    int choice = Console::ProcessMainMenu();
    switch (choice)
    {
    case 1:
        tournament.Start();
        break;
    case 2:
        tournament.Load();
        break;
    case 3:
        exit(0);
    }

    return 0;
}
