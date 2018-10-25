#include "pch.h"
#include "Build.h"

/**********************************************************************
Function Name: get_value
Purpose: To calculate the value of the build
Return Value: The value of the build, an integer value
**********************************************************************/
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

/**********************************************************************
Function Name: get_weight
Purpose: To calculate the weight of the build
Return Value: The weight of the build, an integer value
**********************************************************************/
int Build::get_weight()
{
    int weight = 0;

    for (Set set : m_sets)
    {
        weight += set.get_weight();
    }

    return weight;
}

/**********************************************************************
Function Name: increase
Purpose: To increase the build
Parameters:
    a_card, a Card instance passed by value
**********************************************************************/
void Build::increase(Card a_card)
{
    m_sets[0].add_card(a_card);
}

/**********************************************************************
Function Name: extend
Purpose: To extend the build
Parameters:
    a_set, a Set instance passed by value
**********************************************************************/
void Build::extend(Set a_set)
{
    m_sets.push_back(a_set);
}

/**********************************************************************
Function Name: equals
Purpose: To determine whether the build equals another build
Parameters:
    a_build, a Build instance passed by value
Return Value: Whether the build equals another build, a boolean value
**********************************************************************/
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

/**********************************************************************
Function Name: contains
Purpose: To determine whether the Build contains a set
Parameters:
    a_set, a Set instance, passed by value
Return Value: Whether the build contains a set, a boolean value
**********************************************************************/
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

/**********************************************************************
Function Name: contains
Purpose: To determine whether the Build contains a card
Parameters:
    a_card, a Card instance, passed by value
Return Value: Whether the build contains a card, a boolean value
**********************************************************************/
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
