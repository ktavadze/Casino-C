#include "pch.h"
#include "Table.h"

void Table::AddCard(Card a_card)
{
    m_cards.AddCard(a_card);
}

void Table::RemoveCard(Card a_card)
{
    m_cards.RemoveCard(a_card);
}

void Table::AddBuild(Build a_build)
{
    m_builds.push_back(a_build);
}

bool Table::Contains(Card a_card)
{
    // Check cards
    if (m_cards.Contains(a_card))
    {
        return true;
    }

    // Check builds
    for (Build build : m_builds)
    {
        if (build.Contains(a_card))
        {
            return true;
        }
    }

    return false;
}

string Table::ToString()
{
    string info;

    for (Build build : m_builds)
    {
        info += build.ToString();
    }

    info += m_cards.ToString();

    return info;
}
