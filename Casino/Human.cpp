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

bool Human::MakeMove(Table& a_table)
{
    int choice = Console::ProcessMoveMenu();

    switch (choice)
    {
    case 1:
        // TODO: build
        return false;
    case 2:
        // TODO: capture
        return false;
    case 3:
        if (Trail(a_table))
        {
            return true;
        }
    }

    return false;
}

bool Human::Trail(Table& a_table)
{
    int index = Console::ProcessTrailMenu(m_hand.size());

    Card card = m_hand[index];
    a_table.AddCard(card);
    m_hand.erase(m_hand.begin() + index);

    return true;
}
