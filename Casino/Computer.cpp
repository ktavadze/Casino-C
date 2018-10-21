#include "pch.h"
#include "Computer.h"

int Computer::make_move(Table & a_table)
{
    if (can_build(a_table))
    {
        process_build(a_table);
    }

    if (can_capture(a_table))
    {
        process_capture(a_table);

        return 1;
    }

    for (Card card : m_hand.get_cards())
    {
        if (can_trail(a_table, card))
        {
            trail_player_card(a_table, card);

            return 0;
        }
    }

    return 0;
}

void Computer::process_build(Table & a_table)
{
    vector<Build> possible_builds;

    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
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

            for (Build build : a_table.get_builds())
            {
                if (build.is_human() != m_is_human && build.get_sets().size() == 1)
                {
                    if (count_cards_held(build.get_value() + player_card.get_value()) > 0)
                    {
                        Set build_set;
                        build_set.add_card(player_card);
                        build_set.add_set(build.get_sets().at(0));

                        Build increased_build(m_is_human, build_set);

                        possible_builds.push_back(increased_build);
                    }
                }
            }
        }
    }

    for (Build build : possible_builds)
    {
        cout << endl << build.ToString();
    }
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

void Computer::capture(Table & a_table, Set a_capture_set)
{
    // Capture player card
    capture_player_card(a_capture_set.get_card(0));

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

bool Computer::can_build(Table a_table)
{
    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
            for (Card loose_card : table_loose_set.get_cards())
            {
                if (count_cards_held(loose_card.get_value() + player_card.get_value()) > 0)
                {
                    return true;
                }
            }

            for (Set loose_set : table_loose_sets)
            {
                if (count_cards_held(loose_set.get_value() + player_card.get_value()) > 0)
                {
                    return true;
                }
            }

            for (Build build : a_table.get_builds())
            {
                if (build.is_human() != m_is_human && build.get_sets().size() == 1)
                {
                    if (count_cards_held(build.get_value() + player_card.get_value()) > 0)
                    {
                        return true;
                    }
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

        // Check for matching cards
        for (Card card : table_loose_set.get_cards())
        {
            if (count_cards_held(card.get_value()) > 0)
            {
                return true;
            }
        }

        // Check for matching sets
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
