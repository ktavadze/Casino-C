#include "pch.h"
#include "Table.h"

void Table::add_card(Card a_card)
{
    m_loose_set.add_card(a_card);
}

void Table::remove_card(Card a_card)
{
    m_loose_set.remove_card(a_card);
}

void Table::add_build(Build a_build)
{
    m_builds.push_back(a_build);
}

void Table::remove_build(Build a_build)
{
    for (unsigned int i = 0; i < m_builds.size(); i++)
    {
        if (a_build.equals(m_builds[i]))
        {
            m_builds.erase(m_builds.begin() + i);

            return;
        }
    }
}

void Table::extend_build(int a_index, Set a_set)
{
    m_builds.at(a_index).extend(a_set);
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
    // Check loose set
    if (m_loose_set.contains(a_card))
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

    int count = 0;
    for (Build build : m_builds)
    {
        count++;
        if (count > 1)
        {
            info += " ";
        }
        info += build.ToString();
    }

    if (count > 0)
    {
        info += " ";
    }
    info += m_loose_set.ToString();

    return info;
}
