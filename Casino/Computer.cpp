#include "pch.h"
#include "Computer.h"

int Computer::make_move(Table & a_table)
{
    if (can_capture(a_table))
    {
        Console::display_message("Can capture!");

        process_capture(a_table);
    }
    else {
        for (Card card : m_hand.get_cards())
        {
            if (can_trail(a_table, card))
            {
                // Trail player card
                trail_player_card(a_table, card);

                return 0;
            }
        }
    }

    return 0;
}

void Computer::process_capture(Table & a_table)
{
    // Find all capture options
    vector<vector<Card>> capturable_loose_cards;
    vector<vector<Set>> capturable_loose_sets;
    vector<vector<Build>> capturable_builds;

    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_loose_sets(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        vector<Card> matching_loose_cards;
        vector<Set> matching_loose_sets;
        vector<Build> matching_builds;

        // Check loose set
        if (table_loose_set.get_size() > 0)
        {
            // Check for matching cards
            for (Card card : table_loose_set.get_cards())
            {
                if (card.get_value() == player_card.get_value())
                {
                    cout << endl << card.get_name() << " for " << card.get_weight();

                    matching_loose_cards.push_back(card);
                }
            }

            // Check for matching sets
            if (table_loose_set.get_size() > 1)
            {
                for (Set set : table_loose_sets)
                {
                    if (set.get_value() == player_card.get_value())
                    {
                        cout << endl << set.ToString() << " for " << set.get_weight();

                        matching_loose_sets.push_back(set);
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
                if (build.get_value() == player_card.get_value())
                {
                    cout << endl << build.ToString() << " for " << build.get_weight();

                    matching_builds.push_back(build);
                }
            }
        }

        capturable_loose_cards.push_back(matching_loose_cards);
        capturable_loose_sets.push_back(matching_loose_sets);
        capturable_builds.push_back(matching_builds);
    }

    // Find best capturable loose sets
    vector<Set> best_capturable_loose_sets;

    for (int i = 0; i < m_hand.get_size(); i++)
    {
        Set best_matching_loose_set;

        for (Set set : capturable_loose_sets.at(i))
        {
            if (set.get_weight() > best_matching_loose_set.get_weight())
            {
                best_matching_loose_set = set;
            }
        }

        best_capturable_loose_sets.push_back(best_matching_loose_set);
    }

    // Find best capture option
    int best_option_index = 0;
    int max_capture_weight = 0;

    for (int i = 0; i < m_hand.get_size(); i++)
    {
        int weight = m_hand.get_card(i).get_weight();

        for (Card card : capturable_loose_cards.at(i))
        {
            weight += card.get_weight();
        }

        for (Build build : capturable_builds.at(i))
        {
            weight += build.get_weight();
        }

        weight += best_capturable_loose_sets.at(i).get_weight();

        if (weight == m_hand.get_card(i).get_weight())
        {
            weight = 0;
        }

        if (weight > max_capture_weight)
        {
            best_option_index = i;
            max_capture_weight = weight;
        }
    }

    // Capture
    Card capture_card = m_hand.get_card(best_option_index);
    vector<Card> target_loose_cards = capturable_loose_cards.at(best_option_index);
    Set target_loose_set = best_capturable_loose_sets.at(best_option_index);
    vector<Build> target_builds = capturable_builds.at(best_option_index);

    // Capture player card
    capture_player_card(capture_card);

    // Capture loose cards
    for (Card card : target_loose_cards)
    {
        capture_loose_card(a_table, card);
    }

    // Capture loose set
    for (Card card : target_loose_set.get_cards())
    {
        capture_loose_card(a_table, card);
    }

    // Capture builds
    for (Build build : target_builds)
    {
        capture_build(a_table, build);
    }

    cout << "\n\nWith " << capture_card.get_name();
    cout << " for " << capture_card.get_weight();
    for (Card card : target_loose_cards)
    {
        cout << endl << card.get_name() << " for " << card.get_weight();
    }
    if (target_loose_set.get_size() > 0)
    {
        cout << endl << target_loose_set.ToString();
        cout << " for " << target_loose_set.get_weight();
    }
    for (Build build : target_builds)
    {
        cout << endl << build.ToString() << " for " << build.get_weight();
    }
}

bool Computer::can_capture(Table a_table)
{
    // Check loose set
    if (a_table.get_loose_set().get_size() > 0)
    {
        Set loose_set = a_table.get_loose_set();

        // Check for matching cards
        for (Card card : loose_set.get_cards())
        {
            if (count_cards_held(card.get_value()) > 0)
            {
                return true;
            }
        }

        // Check for matching sets
        if (loose_set.get_size() > 1)
        {
            vector<Set> loose_sets = generate_loose_sets(loose_set);

            for (Set set : loose_sets)
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

vector<Set> Computer::generate_loose_sets(Set a_loose_set)
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
