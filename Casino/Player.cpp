#include "pch.h"
#include "Player.h"

using namespace std;

bool Player::MakeMove(Table& a_table)
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

bool Player::Trail(Table& a_table)
{
    int index = Console::ProcessTrailMenu(m_hand) - 1;

    Card card = m_hand[index];
    a_table.AddCard(card);
    m_hand.erase(m_hand.begin() + index);

    return true;
}

string Player::ToString()
{
    string info;

    info += "\n    Score: " + m_score;

    info += "\n    Hand:";
    for (Card card : m_hand)
    {
        info += " " + card.get_name();
    }

    info += "\n    Pile:";
    for (Card card : m_pile)
    {
        info += " " + card.get_name();
    }

    return info;
}
