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

void Table::add_build(Build a_build)
{
    m_builds.push_back(a_build);
}

void Table::remove_build(Build a_build)
{
    int index = index_of(a_build);

    m_builds.erase(m_builds.begin() + index);
}

int Table::index_of(Build a_build)
{
    for (unsigned int i = 0; i < m_builds.size(); i++)
    {
        if (a_build.equals(m_builds[i]))
        {
            return i;
        }
    }

    return -1;
}

bool Table::contains(Build a_build)
{
    for (Build build : m_builds)
    {
        if (build.equals(a_build))
        {
            return true;
        }
    }

    return false;
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
