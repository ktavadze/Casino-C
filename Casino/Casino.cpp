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
            bool won_toss = Console::process_coin_toss();

            Tournament tournament(won_toss);

            tournament.start();

            break;
        }
        case 2:
        {
            Tournament tournament;

            Serialization::load_game(tournament);

            tournament.start();

            break;
        }
        case 3:
            return 0;
        }
    }
}
