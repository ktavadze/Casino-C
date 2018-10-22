#include "pch.h"
#include "Computer.h"

int Computer::make_move(Table & a_table)
{
    if (can_build(a_table))
    {
        process_build(a_table);
    }
    else if (can_capture(a_table))
    {
        process_capture(a_table);

        return 1;
    }
    else {
        process_trail(a_table);
    }

    return 0;
}

void Computer::process_build(Table & a_table)
{
    Build best_build = find_best_build(a_table);

    create_build(a_table, best_build);
}

void Computer::process_capture(Table & a_table)
{
    Set best_capture_set = find_best_capture_set(a_table);

    capture(a_table, best_capture_set);
}

void Computer::process_trail(Table & a_table)
{
    Card best_trail_card = find_best_trail_card(a_table);

    trail(a_table, best_trail_card);
}

void Computer::create_build(Table & a_table, Build a_build)
{
    Set build_set = a_build.get_sets().at(0);

    // Remove player card from hand
    m_hand.remove_card(build_set.get_card(0));

    // Remove loose set from table
    for (Card card : a_table.get_loose_set().get_cards())
    {
        if (build_set.contains(card))
        {
            a_table.remove_loose_card(card);
        }
    }

    // Add build to table
    a_table.add_build(a_build);
}

void Computer::capture(Table & a_table, Set a_capture_set)
{
    // Remove capture card from hand
    m_hand.remove_card(a_capture_set.get_card(0));

    // Add capture card to pile
    m_pile.add_card(a_capture_set.get_card(0));

    // Capture loose set
    for (Card card : a_table.get_loose_set().get_cards())
    {
        if (a_capture_set.contains(card))
        {
            capture_loose_card(a_table, card);
        }
    }

    // Capture builds
    for (Build build : a_table.get_builds())
    {
        if (a_capture_set.contains(build.get_sets()))
        {
            capture_build(a_table, build);
        }
    }
}

void Computer::trail(Table & a_table, Card a_trail_card)
{
    // Remove trail card from hand
    m_hand.remove_card(a_trail_card);

    // Add trail card to table
    a_table.add_loose_card(a_trail_card);
}

bool Computer::can_build(Table a_table)
{
    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
            // Check for possible simple builds
            for (Card loose_card : table_loose_set.get_cards())
            {
                if (count_cards_held(loose_card.get_value() + player_card.get_value()) > 0)
                {
                    return true;
                }
            }

            // Check for possible compound builds
            for (Set loose_set : table_loose_sets)
            {
                if (count_cards_held(loose_set.get_value() + player_card.get_value()) > 0)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Computer::can_capture(Table a_table)
{
    // Check loose set
    if (a_table.get_loose_set().get_size() > 0)
    {
        Set table_loose_set = a_table.get_loose_set();

        // Check for matching loose cards
        for (Card card : table_loose_set.get_cards())
        {
            if (count_cards_held(card.get_value()) > 0)
            {
                return true;
            }
        }

        // Check for matching loose sets
        if (table_loose_set.get_size() > 1)
        {
            vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

            for (Set set : table_loose_sets)
            {
                if (count_cards_held(set.get_value()) > 0)
                {
                    return true;
                }
            }
        }
    }

    // Check builds
    if (!a_table.get_builds().empty())
    {
        // Check for matching builds
        for (Build build : a_table.get_builds())
        {
            if (count_cards_held(build.get_value()) > 0)
            {
                return true;
            }
        }
    }

    return false;
}
