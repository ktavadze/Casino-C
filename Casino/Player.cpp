#include "pch.h"
#include "Player.h"

string Player::ToString()
{
    string info;

    info += "\n   Score: " + to_string(m_score);

    info += "\n   Hand: " + m_hand.ToString();

    info += "\n   Pile: " + m_pile.ToString();

    return info;
}

void Player::capture_loose_card(Table & a_table, Card a_card)
{
    // Add loose card to pile
    m_pile.add_card(a_card);

    // Remove loose card from table
    a_table.remove_loose_card(a_card);
}

void Player::capture_build(Table & a_table, Build a_build)
{
    // Add build to pile
    for (Set set : a_build.get_sets())
    {
        m_pile.add_set(set);
    }

    // Remove build from table
    a_table.remove_build(a_build);
}

bool Player::reserved_for_capture(Table a_table, Card a_card)
{
    for (Build build : a_table.get_builds())
    {
        if (build.get_value() == a_card.get_value() && build.is_human() == m_is_human)
        {
            if (count_cards_held(a_card.get_value()) < 2)
            {
                return true;
            }
        }
    }

    return false;
}

bool Player::owns_build(Table a_table)
{
    for (Build build : a_table.get_builds())
    {
        if (build.is_human() == m_is_human)
        {
            return true;
        }
    }

    return false;
}

int Player::count_cards_held(int a_value)
{
    int count = 0;

    for (Card card : m_hand.get_cards())
    {
        if (card.get_value() == a_value)
        {
            count++;
        }
    }

    return count;
}
