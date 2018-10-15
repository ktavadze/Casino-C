#include "pch.h"
#include "Computer.h"

int Computer::make_move(Table & a_table)
{
    if (can_capture(a_table))
    {
        Console::display_message("Can capture!");
    }

    for (Card card : m_hand.get_cards())
    {
        if (can_trail(a_table, card))
        {
            // Add trail card to table
            a_table.add_loose_card(card);

            // Remove trail card from hand
            m_hand.remove_card(card);

            return 0;
        }
    }

    return 0;
}

void Computer::process_capture(Table & a_table)
{
    vector<Build> matching_builds;
    vector<Set> matching_loose_sets;
    vector<Card> matching_loose_cards;

    // Check builds
    if (!a_table.get_builds().empty())
    {
        // Check for matching builds
        for (Build build : a_table.get_builds())
        {
            if (count_cards_held(build.get_value()) > 0)
            {
                matching_builds.push_back(build);
            }
        }
    }

    // Check loose set
    if (a_table.get_loose_set().get_size() > 0)
    {
        Set loose_set = a_table.get_loose_set();

        // Check for matching cards
        for (Card card : loose_set.get_cards())
        {
            if (count_cards_held(card.get_value()) > 0)
            {
                matching_loose_cards.push_back(card);
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
                    matching_loose_sets.push_back(set);
                }
            }
        }
    }
}

bool Computer::can_capture(Table a_table)
{
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
