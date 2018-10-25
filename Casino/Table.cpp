#include "pch.h"
#include "Table.h"

/**********************************************************************
Function Name: add_loose_card
Purpose: To add a loose card to the table
Parameters:
    a_card, a Card instance passed by value
**********************************************************************/
void Table::add_loose_card(Card a_card)
{
    m_loose_set.add_card(a_card);
}

/**********************************************************************
Function Name: remove_loose_card
Purpose: To remove a loose card from the table
Parameters:
    a_card, a Card instance passed by value
**********************************************************************/
void Table::remove_loose_card(Card a_card)
{
    m_loose_set.remove_card(a_card);
}

/**********************************************************************
Function Name: remove_loose_set
Purpose: To remove a loose set from the table
Parameters:
    a_set, a Set instance passed by value
**********************************************************************/
void Table::remove_loose_set(Set a_set)
{
    m_loose_set.remove_set(a_set);
}

/**********************************************************************
Function Name: add_build
Purpose: To add a build to the table
Parameters:
    a_build, a Build instance passed by value
**********************************************************************/
void Table::add_build(Build a_build)
{
    m_builds.push_back(a_build);
}

/**********************************************************************
Function Name: remove_build
Purpose: To remove a build from the table
Parameters:
    a_build, a Build instance passed by value
**********************************************************************/
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

/**********************************************************************
Function Name: increase_build
Purpose: To increase a build on the table
Parameters:
    a_index, an integer. Represents the index of the build being increased
    a_card, a Card instance, passed by value. Represents the card with which
        the build will be increased
    a_is_human, a boolean. Represents the owner of the increased build
**********************************************************************/
void Table::increase_build(int a_index, Card a_card, bool a_is_human)
{
    m_builds.at(a_index).increase(a_card);
    m_builds.at(a_index).is_human(a_is_human);
}

/**********************************************************************
Function Name: extend_build
Purpose: To extend a build on the table
Parameters:
    a_index, an integer. Represents the index of the build being extended
    a_set, a Set instance, passed by value. Represents the set with which
        the build will be extended
    a_is_human, a boolean. Represents the owner of the extended build
**********************************************************************/
void Table::extend_build(int a_index, Set a_set, bool a_is_human)
{
    m_builds.at(a_index).extend(a_set);
    m_builds.at(a_index).is_human(a_is_human);
}

/**********************************************************************
Function Name: contains
Purpose: To determine whether the table contains a build
Parameters:
    a_build, a Build instance, passed by value
Return Value: Whether the set contains a build, a boolean value
**********************************************************************/
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

/**********************************************************************
Function Name: contains
Purpose: To determine whether the table contains a card
Parameters:
    a_card, a Card instance, passed by value
Return Value: Whether the set contains a card, a boolean value
**********************************************************************/
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
