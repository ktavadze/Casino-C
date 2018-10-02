#include "pch.h"
#include "Build.h"

bool Build::increase(Card a_card)
{
    if (m_sets.size() == 1)
    {
        m_value += a_card.get_value();

        m_sets[0].add_card(a_card);

        return true;
    }

    return false;
}

bool Build::extend(Set a_set)
{
    if (m_value == a_set.get_value())
    {
        m_sets.push_back(a_set);

        return true;
    }

    return false;
}

bool Build::equals(Build a_build)
{
    // Check size
    if (a_build.get_sets().size() != m_sets.size())
    {
        return false;
    }

    // Check owner
    if (a_build.is_human() != m_is_human)
    {
        return false;
    }

    // Check sets
    for (Set set : a_build.get_sets())
    {
        if (!contains(set))
        {
            return false;
        }
    }

    return true;
}

bool Build::contains(Set a_set)
{
    for (Set set : m_sets)
    {
        if (set.equals(a_set))
        {
            return true;
        }
    }

    return false;
}

bool Build::contains(Card a_card)
{
    for (Set set : m_sets)
    {
        if (set.contains(a_card))
        {
            return true;
        }
    }

    return false;
}

string Build::ToString()
{
    string info;

    info += "[";

    for (Set set : m_sets)
    {
        info += " [" + set.ToString() + "]";
    }

    info += " ] ";

    return info;
}
