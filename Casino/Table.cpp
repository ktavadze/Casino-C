#include "pch.h"
#include "Table.h"

void Table::add_card(Card a_card)
{
    m_cards.add_card(a_card);
}

void Table::remove_card(Card a_card)
{
    m_cards.remove_card(a_card);
}

void Table::AddBuild(Build a_build)
{
    m_builds.push_back(a_build);
}

bool Table::contains(Card a_card)
{
    // Check cards
    if (m_cards.contains(a_card))
    {
        return true;
    }

    // Check builds
    for (Build build : m_builds)
    {
        if (build.contains(a_card))
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
