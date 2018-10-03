#include "pch.h"
#include "Set.h"

void Set::add_card(Card a_card)
{
    m_value += a_card.get_value();

    m_cards.push_back(a_card);
}

void Set::add_set(Set a_set)
{
    for (Card card : a_set.get_cards())
    {
        add_card(card);
    }
}

void Set::add_sets(vector<Set> a_sets)
{
    for (Set set : a_sets)
    {
        add_set(set);
    }
}

void Set::remove_card(Card a_card)
{
    int index = find(m_cards.begin(), m_cards.end(), a_card) - m_cards.begin();

    m_cards.erase(m_cards.begin() + index);
}

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
