#include "pch.h"
#include "Build.h"

bool Build::AddCard(Card a_card)
{
    if (m_cards.size() == 1)
    {
        m_value += a_card.get_value();

        m_cards[0].push_back(a_card);

        return true;
    }

    return false;
}

bool Build::AddBuild(vector<Card> a_cards)
{
    int value = 0;
    for (Card card : a_cards)
    {
        value += card.get_value();
    }

    if (m_value == value)
    {
        m_cards.push_back(a_cards);

        return true;
    }

    return false;
}

bool Build::Contains(Card a_card)
{
    for (vector<Card> v : m_cards)
    {
        for (Card card : v)
        {
            if (card == a_card)
            {
                return true;
            }
        }
    }

    return false;
}

string Build::ToString()
{
    string info;

    info += " [";

    for (vector<Card> v : m_cards)
    {
        info += " [";

        int count = 0;
        for (Card card : v)
        {
            if (count > 0)
            {
                info += " ";
            }
            info += card.get_name();
            count++;
        }

        info += "]";
    }

    info += " ]";

    return info;
}
