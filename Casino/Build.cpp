#include "pch.h"
#include "Build.h"

int Build::get_value()
{
    int value = 0;

    if (!m_sets.empty())
    {
        for (Card card : m_sets[0].get_cards())
        {
            value += card.get_value();
        }
    }

    return value;
}

int Build::get_weight()
{
    int weight = 0;

    for (Set set : m_sets)
    {
        weight += set.get_weight();
    }

    return weight;
}

void Build::increase(Card a_card)
{
    m_sets[0].add_card(a_card);
}

void Build::extend(Set a_set)
{
    m_sets.push_back(a_set);
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

    info += " ]";

    return info;
}
