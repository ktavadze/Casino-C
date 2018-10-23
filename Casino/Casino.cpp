/***********************************************************
* Name: Konstantine Tavadze                                *
* Project: Casino                                          *
* Class: OPL                                               *
* Date: 10/24/18                                           *
***********************************************************/
#include "pch.h"
#include "Tournament.h"

using namespace std;

int main()
{
    for (;;)
    {
        int choice = Console::process_main_menu();

        switch (choice)
        {
        case 1:
        {
            Tournament tournament;

            tournament.start();

            break;
        }
        case 2:
        {
            Tournament tournament = Serialization::load_game();

            tournament.start();

            break;
        }
        case 3:
            return 0;
        }
    }
}
