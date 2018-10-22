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
    // Find possible builds
    vector<Build> possible_builds;

    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
            // Find possible simple builds
            for (Card loose_card : table_loose_set.get_cards())
            {
                if (count_cards_held(loose_card.get_value() + player_card.get_value()) > 0)
                {
                    Set build_set;
                    build_set.add_card(player_card);
                    build_set.add_card(loose_card);

                    Build build(m_is_human, build_set);

                    possible_builds.push_back(build);
                }
            }

            // Find possible compund builds
            for (Set loose_set : table_loose_sets)
            {
                if (count_cards_held(loose_set.get_value() + player_card.get_value()) > 0)
                {
                    Set build_set;
                    build_set.add_card(player_card);
                    build_set.add_set(loose_set);

                    Build build(m_is_human, build_set);

                    possible_builds.push_back(build);
                }
            }
        }
    }

    // Find best possible build
    Build best_possible_build;

    for (Build build : possible_builds)
    {
        if (build.get_weight() > best_possible_build.get_weight())
        {
            best_possible_build = build;
        }

        cout << endl << build.ToString() << " for " << build.get_weight();
    }

    create_build(a_table, best_possible_build);

    cout << "\n\nBuilding: " << best_possible_build.ToString() << " for " << best_possible_build.get_weight();
}

void Computer::process_capture(Table & a_table)
{
    // Find possible capture sets
    vector<Set> possible_capture_sets;

    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        Set matching_loose_cards;
        Set best_matching_loose_set;
        vector<Build> matching_builds;

        // Check loose set
        if (table_loose_set.get_size() > 0)
        {
            // Find all matching loose cards
            for (Card card : table_loose_set.get_cards())
            {
                if (card.get_value() == player_card.get_value())
                {
                    matching_loose_cards.add_card(card);
                }
            }

            // Find best matching loose set
            if (table_loose_set.get_size() > 1)
            {
                for (Set set : table_loose_sets)
                {
                    if (set.get_value() == player_card.get_value())
                    {
                        if (set.get_weight() > best_matching_loose_set.get_weight())
                        {
                            best_matching_loose_set = set;
                        }
                    }
                }
            }
        }

        // Check builds
        if (!a_table.get_builds().empty())
        {
            // Find all matching builds
            for (Build build : a_table.get_builds())
            {
                if (build.get_value() == player_card.get_value())
                {
                    matching_builds.push_back(build);
                }
            }
        }

        // Construct capture set
        Set best_capturable_set;

        best_capturable_set.add_card(player_card);
        best_capturable_set.add_set(matching_loose_cards);
        best_capturable_set.add_set(best_matching_loose_set);

        for (Build build : matching_builds)
        {
            for (Set set : build.get_sets())
            {
                best_capturable_set.add_set(set);
            }
        }

        // Save capture set
        if (best_capturable_set.get_size() > 1)
        {
            possible_capture_sets.push_back(best_capturable_set);
        }
    }

    // Find best capture set
    Set best_capture_set;

    for (Set set : possible_capture_sets)
    {
        if (set.get_weight() > best_capture_set.get_weight())
        {
            best_capture_set = set;
        }

        cout << endl << set.ToString() << " for " << set.get_weight();
    }

    capture(a_table, best_capture_set);

    cout << "\n\nCapturing: " << best_capture_set.ToString() << " for " << best_capture_set.get_weight();
}

void Computer::process_trail(Table & a_table)
{
    // Find best trail card
    Card best_trail_card;

    for (Card card : m_hand.get_cards())
    {
        if (best_trail_card.get_weight() == 0)
        {
            best_trail_card = card;
        }
        else if (card.get_weight() < best_trail_card.get_weight())
        {
            best_trail_card = card;
        }
    }

    trail(a_table, best_trail_card);

    cout << "\n\nTrailing: " << best_trail_card.get_name() << " for " << best_trail_card.get_weight();
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

bool Computer::vector_contains_set(vector<Set> a_vector, Set a_set)
{
    for (Set set : a_vector)
    {
        if (set.equals(a_set))
        {
            return true;
        }
    }

    return false;
}

vector<Set> Computer::generate_set_combinations(Set a_loose_set)
{
    vector<Set> loose_sets;

    // Generate doubles
    if (a_loose_set.get_size() > 1)
    {
        for (int i = 0; i < a_loose_set.get_size(); i++)
        {
            for (int j = 0; j < a_loose_set.get_size(); j++)
            {
                if (i != j)
                {
                    Set set;
                    set.add_card(a_loose_set.get_card(i));
                    set.add_card(a_loose_set.get_card(j));

                    if (set.get_value() < 14)
                    {
                        if (!vector_contains_set(loose_sets, set))
                        {
                            loose_sets.push_back(set);
                        }
                    }
                }
            }
        }
    }

    // Generate triples
    if (a_loose_set.get_size() > 2)
    {
        for (int i = 0; i < a_loose_set.get_size(); i++)
        {
            for (int j = 0; j < a_loose_set.get_size(); j++)
            {
                for (int k = 0; k < a_loose_set.get_size(); k++)
                {
                    if (i != j && i != k && j != k)
                    {
                        Set set;
                        set.add_card(a_loose_set.get_card(i));
                        set.add_card(a_loose_set.get_card(j));
                        set.add_card(a_loose_set.get_card(k));

                        if (set.get_value() < 14)
                        {
                            if (!vector_contains_set(loose_sets, set))
                            {
                                loose_sets.push_back(set);
                            }
                        }
                    }
                }
            }
        }
    }

    return loose_sets;
}
