#include "pch.h"
#include "Set.h"

void Set::AddCard(Card a_card)
{
    m_value += a_card.get_value();

    m_cards.push_back(a_card);
}

void Set::RemoveCard(Card a_card)
{
    int index = find(m_cards.begin(), m_cards.end(), a_card) - m_cards.begin();

    m_cards.erase(m_cards.begin() + index);
}

Card Set::Get(int a_index)
{
    return m_cards.at(a_index);
}

void Set::Clear()
{
    m_cards.clear();
}

int Set::Size()
{
    return m_cards.size();
}

bool Set::Empty()
{
    return m_cards.empty();
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

    return info;
}
