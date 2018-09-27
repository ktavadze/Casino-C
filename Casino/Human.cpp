#include "pch.h"
#include "Human.h"

using namespace std;

void Human::Play(Table& a_table)
{
    while (true)
    {
        int choice = Console::ProcessHumanTurnMenu();

        switch (choice)
        {
        case 1:
            // TODO: save game
            exit(0);
        case 2:
            if (MakeMove(a_table))
            {
                return;
            }
            break;
        case 3:
            // TODO: ask for help
            exit(0);
        case 4:
            exit(0);
        }
    }
}
