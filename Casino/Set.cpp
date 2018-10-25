#include "pch.h"
#include "Set.h"

/**********************************************************************
Function Name: get_value
Purpose: To calculate the value of a set
Return Value: The value of a set, an integer value
**********************************************************************/
int Set::get_value()
{
    int value = 0;

    for (Card card : m_cards)
    {
        value += card.get_value();
    }

    return value;
}

/**********************************************************************
Function Name: get_weight
Purpose: To calculate the weight of a set
Return Value: The weight of a set, an integer value
**********************************************************************/
int Set::get_weight()
{
    int weight = 0;

    for (Card card : m_cards)
    {
        weight += card.get_weight();
    }

    return weight;
}

/**********************************************************************
Function Name: add_card
Purpose: To add a card to the set
Parameters:
    a_card, an Card instance passed by value
**********************************************************************/
void Set::add_card(Card a_card)
{
    m_cards.push_back(a_card);
}

/**********************************************************************
Function Name: remove_card
Purpose: To remove a card from the set
Parameters:
    a_card, an Card instance passed by value
**********************************************************************/
void Set::remove_card(Card a_card)
{
    // Find card
    int index = find(m_cards.begin(), m_cards.end(), a_card) - m_cards.begin();

    m_cards.erase(m_cards.begin() + index);
}

/**********************************************************************
Function Name: add_set
Purpose: To add a set to the set
Parameters:
    a_set, a Set instance passed by value
**********************************************************************/
void Set::add_set(Set a_set)
{
    for (Card card : a_set.get_cards())
    {
        add_card(card);
    }
}

/**********************************************************************
Function Name: remove_set
Purpose: To remove a set from the set
Parameters:
    a_set, a Set instance passed by value
**********************************************************************/
void Set::remove_set(Set a_set)
{
    for (Card card : a_set.get_cards())
    {
        remove_card(card);
    }
}

/**********************************************************************
Function Name: equals
Purpose: To determine whether the set equals another set
Parameters:
    a_set, a Set instance passed by value
Return Value: Whether the set equals another set, a boolean value
**********************************************************************/
bool Set::equals(Set a_set)
{
    // Check size
    if (a_set.get_size() != get_size())
    {
        return false;
    }

    // Check cards
    for (Card card : a_set.get_cards())
    {
        if (!contains(card))
        {
            return false;
        }
    }

    return true;
}

/**********************************************************************
Function Name: contains
Purpose: To determine whether the set contains a vector of sets
Parameters:
    a_sets, a vector of Set instances, passed by value
Return Value: Whether the set contains a vector of sets, a boolean value
**********************************************************************/
bool Set::contains(vector<Set> a_sets)
{
    for (Set set : a_sets)
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
Purpose: To determine whether the set contains another set
Parameters:
    a_set, a Set instance, passed by value
Return Value: Whether the set contains another set, a boolean value
**********************************************************************/
bool Set::contains(Set a_set)
{
    for (Card card : a_set.get_cards())
    {
        if (!contains(card))
        {
            return false;
        }
    }

    return true;
}

/**********************************************************************
Function Name: contains
Purpose: To determine whether the set contains a card
Parameters:
    a_card, a Card instance, passed by value
Return Value: Whether the set contains a card, a boolean value
**********************************************************************/
bool Set::contains(Card a_card)
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
