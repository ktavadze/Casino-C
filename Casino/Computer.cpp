#include "pch.h"
#include "Computer.h"

using namespace std;

void Computer::Play(Table& a_table)
{
    while (true)
    {
        int choice = Console::ProcessComputerTurnMenu();

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
            exit(0);
        }
    }
}
