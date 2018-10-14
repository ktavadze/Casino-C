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

bool Player::can_create_build(Table a_table, Card a_build_card, Set a_loose_set)
{
    // Check build card
    if (reserved_for_capture(a_table, a_build_card))
    {
        Console::display_message("ERROR: build card reserved for capture!");

        return false;
    }

    // Check build value
    if (count_cards_held(a_build_card.get_value() + a_loose_set.get_value()) == 0)
    {
        Console::display_message("ERROR: no card in hand matching build value!");

        return false;
    }

    return true;
}

bool Player::can_increase_build(Table a_table, Build a_selected_build, Card a_build_card)
{
    // Check build card
    if (reserved_for_capture(a_table, a_build_card))
    {
        Console::display_message("ERROR: build card reserved for capture!");

        return false;
    }

    // Check build owner
    if (a_selected_build.is_human() == m_is_human)
    {
        Console::display_message("ERROR: cannot increase own build!");

        return false;
    }

    // Check build size
    if (a_selected_build.get_sets().size() > 1)
    {
        Console::display_message("ERROR: cannot increase multi-builds!");

        return false;
    }

    // Check build value
    if (count_cards_held(a_build_card.get_value() + a_selected_build.get_value()) == 0)
    {
        Console::display_message("ERROR: no card in hand matching build value!");

        return false;
    }

    return true;
}

bool Player::can_extend_build(Table a_table, Build a_selected_build, Card a_build_card, Set a_loose_set)
{
    // Check build card
    if (reserved_for_capture(a_table, a_build_card))
    {
        Console::display_message("ERROR: build card reserved for capture!");

        return false;
    }

    // Check build value
    if (a_build_card.get_value() + a_loose_set.get_value() != a_selected_build.get_value())
    {
        Console::display_message("ERROR: build sum mismatch!");

        return false;
    }

    return true;
}

bool Player::can_capture(Table a_table, Card a_capture_card, Set a_loose_set, Set a_firm_set)
{
    // Check loose set
    if (a_loose_set.get_size() > 0)
    {
        int sum = 0;

        for (Card card : a_loose_set.get_cards())
        {
            if (card.get_value() != a_capture_card.get_value())
            {
                sum += card.get_value();
            }
        }

        // Check loose sum
        if (sum != 0 && sum != a_capture_card.get_value())
        {
            Console::display_message("ERROR: cannot capture selected loose card(s)!");

            return false;
        }
    }

    for (Card card : a_table.get_loose_set().get_cards())
    {
        if (card.get_value() == a_capture_card.get_value())
        {
            if (!a_loose_set.contains(card))
            {
                Console::display_message("ERROR: must capture matching loose card(s)!");

                return false;
            }
        }
    }

    // Check firm set
    if (a_firm_set.get_size() > 0)
    {
        int matching_builds = 0;
        int captured_builds = 0;
        int cards_found = 0;

        for (Build build : a_table.get_builds())
        {
            if (build.get_value() == a_capture_card.get_value() && build.is_human() == m_is_human)
            {
                matching_builds++;

                if (a_firm_set.contains(build.get_sets()))
                {
                    captured_builds++;

                    for (Set set : build.get_sets())
                    {
                        cards_found += set.get_size();
                    }
                }
            }
        }

        if (cards_found != a_firm_set.get_size())
        {
            Console::display_message("ERROR: cannot capture selected build card(s)!");

            return false;
        }

        if (matching_builds != captured_builds)
        {
            if (reserved_for_capture(a_table, a_capture_card))
            {
                Console::display_message("ERROR: must capture matching owned build(s)!");

                return false;
            }
        }
    }
    else
    {
        for (Build build : a_table.get_builds())
        {
            if (build.get_value() == a_capture_card.get_value() && build.is_human() == m_is_human)
            {
                if (reserved_for_capture(a_table, a_capture_card))
                {
                    Console::display_message("ERROR: must capture matching owned build(s)!");

                    return false;
                }
            }
        }
    }

    return true;
}

bool Player::can_trail(Table a_table, Card a_trail_card)
{
    // Check trail card
    if (reserved_for_capture(a_table, a_trail_card))
    {
        Console::display_message("ERROR: trail card reserved for capture!");

        return false;
    }

    // Check builds
    if (owns_build(a_table))
    {
        Console::display_message("ERROR: cannot trail while owner of build(s)!");

        return false;
    }

    // Check loose set
    for (Card card : a_table.get_loose_set().get_cards())
    {
        if (card.get_value() == a_trail_card.get_value())
        {
            Console::display_message("ERROR: must capture matching loose card(s)!");

            return false;
        }
    }

    return true;
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
