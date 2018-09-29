#include "pch.h"
#include "Table.h"

void Table::AddCard(Card a_card)
{
    m_cards.push_back(a_card);
}

void Table::RemoveCard(Card a_card)
{
    int index = find(m_cards.begin(), m_cards.end(), a_card) - m_cards.begin();
    m_cards.erase(m_cards.begin() + index);
}

void Table::AddBuild(Build a_build)
{
    m_builds.push_back(a_build);
}

string Table::ToString()
{
    string info;

    for (Build build : m_builds)
    {
        info += build.ToString();
    }

    for (Card card : m_cards)
    {
        info += " " + card.get_name();
    }

    return info;
}
