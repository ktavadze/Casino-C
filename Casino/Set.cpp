#include "pch.h"
#include "Set.h"

void Set::AddCard(Card a_card)
{
    m_value += a_card.get_value();

    m_cards.push_back(a_card);
}

bool Set::Contains(Card a_card)
{
    for (Card card : m_cards)
    {
        if (card == a_card)
        {
            return true;
        }
    }

    return false;
}

string Set::ToString()
{
    string info;

    info += " [";

    int count = 0;
    for (Card card : m_cards)
    {
        count++;
        if (count > 1)
        {
            info += " ";
        }
        info += card.get_name();
    }

    info += "]";

    return info;
}
