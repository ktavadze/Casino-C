#include "pch.h"
#include "Player.h"

using namespace std;

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
