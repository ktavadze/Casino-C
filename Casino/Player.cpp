#include "pch.h"
#include "Player.h"

/**********************************************************************
Function Name: ask_for_help
Purpose: To allow the player to ask for help
Parameters:
    a_table, a Table instance passed by value
**********************************************************************/
void Player::ask_for_help(Table a_table)
{
    if (can_increase(a_table))
    {
        find_best_increase(a_table);
    }
    else if (can_extend(a_table))
    {
        find_best_extend(a_table);
    }
    else if (can_create(a_table))
    {
        find_best_create(a_table);
    }
    else if (can_capture(a_table))
    {
        find_best_caputre(a_table);
    }
    else {
        find_best_trail(a_table);
    }
}

string Player::ToString()
{
    string info;

    info += "\n   Score: " + to_string(m_score);

    info += "\n   Hand: " + m_hand.ToString();

    info += "\n   Pile: " + m_pile.ToString();

    return info;
}

/**********************************************************************
Function Name: capture_loose_card
Purpose: To capture a loose card
Parameters:
    a_table, a Table instace passed by reference
    a_card, a Card instance passed by value
**********************************************************************/
void Player::capture_loose_card(Table & a_table, Card a_card)
{
    // Add loose card to pile
    m_pile.add_card(a_card);

    // Remove loose card from table
    a_table.remove_loose_card(a_card);
}

/**********************************************************************
Function Name: capture_build
Purpose: To capture a build
Parameters:
    a_table, a Table instace passed by reference
    a_build, a Build instance passed by value
**********************************************************************/
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

/**********************************************************************
Function Name: can_increase
Purpose: To determine whether the player can increase any builds
Parameters:
    a_table, a Table instace passed by value
Return Value: Whether the player can increase any builds, a boolean value
**********************************************************************/
bool Player::can_increase(Table a_table)
{
    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
            // Check for possible increased builds
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

/**********************************************************************
Function Name: can_extend
Purpose: To determine whether the player can extend any builds
Parameters:
    a_table, a Table instace passed by value
Return Value: Whether the player can extend any builds, a boolean value
**********************************************************************/
bool Player::can_extend(Table a_table)
{
    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
            // Find all simple builds
            for (Card loose_card : table_loose_set.get_cards())
            {
                if (count_cards_held(loose_card.get_value() + player_card.get_value()) > 0)
                {
                    Set build_set;
                    build_set.add_card(player_card);
                    build_set.add_card(loose_card);

                    // Check for possible extended builds
                    for (Build table_build : a_table.get_builds())
                    {
                        if (table_build.get_value() == build_set.get_value())
                        {
                            return true;
                        }
                    }
                }
            }

            // Find all compund builds
            for (Set loose_set : table_loose_sets)
            {
                if (count_cards_held(loose_set.get_value() + player_card.get_value()) > 0)
                {
                    Set build_set;
                    build_set.add_card(player_card);
                    build_set.add_set(loose_set);

                    // Check for possible extended builds
                    for (Build table_build : a_table.get_builds())
                    {
                        if (table_build.get_value() == build_set.get_value())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

/**********************************************************************
Function Name: can_create
Purpose: To determine whether the player create any builds
Parameters:
    a_table, a Table instace passed by value
Return Value: Whether the player can create any builds, a boolean value
**********************************************************************/
bool Player::can_create(Table a_table)
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

/**********************************************************************
Function Name: can_capture
Purpose: To determine whether the player can capture anything
Parameters:
    a_table, a Table instace passed by value
Return Value: Whether the player can capture anything, a boolean value
**********************************************************************/
bool Player::can_capture(Table a_table)
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

/**********************************************************************
Function Name: reserved_for_capture
Purpose: To determine whether a card is reserved for capture
Parameters:
    a_table, a Table instace passed by value
    a_card, a Card instance passed by value
Return Value: Whether a card is reserved for capture, a boolean value
**********************************************************************/
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

/**********************************************************************
Function Name: owns_build
Purpose: To determine whether the player owns any builds
Parameters:
    a_table, a Table instace passed by value
Return Value: Whether the player owns any builds, a boolean value
**********************************************************************/
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

/**********************************************************************
Function Name: count_cards_held
Purpose: To calculate the number of cards of specified value in hand
Parameters:
    a_value, an integer
Return Value: The number of cards of specified value in held, an integer value
**********************************************************************/
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

/**********************************************************************
Function Name: find_best_increase
Purpose: To find the best increased build
Parameters:
    a_table, a Table instace passed by value
Return Value: The best increased build, a Build instance
**********************************************************************/
Build Player::find_best_increase(Table a_table)
{
    // Find possible builds
    vector<Build> possible_builds;

    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
            // Find possible increased builds
            for (Build build : a_table.get_builds())
            {
                if (build.is_human() != m_is_human && build.get_sets().size() == 1)
                {
                    if (count_cards_held(build.get_value() + player_card.get_value()) > 0)
                    {
                        build.increase(player_card);

                        possible_builds.push_back(build);
                    }
                }
            }
        }
    }

    // Find best build
    Build best_build;

    for (Build build : possible_builds)
    {
        if (build.get_weight() > best_build.get_weight())
        {
            best_build = build;
        }
    }

    cout << "\nWith " << best_build.get_sets().at(0).get_cards().back().get_name();
    cout << " increase " << best_build.ToString() << endl;
    cout << "Heuristic: " << best_build.get_weight() << endl;

    return best_build;
}

/**********************************************************************
Function Name: find_best_extend
Purpose: To find the best extended build
Parameters:
    a_table, a Table instace passed by value
Return Value: The best extended build, a Build instance
**********************************************************************/
Build Player::find_best_extend(Table a_table)
{
    // Find possible builds
    vector<Build> possible_builds;

    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
            // Find all simple builds
            for (Card loose_card : table_loose_set.get_cards())
            {
                if (count_cards_held(loose_card.get_value() + player_card.get_value()) > 0)
                {
                    Set build_set;
                    build_set.add_card(player_card);
                    build_set.add_card(loose_card);

                    // Find possible extended builds
                    for (Build table_build : a_table.get_builds())
                    {
                        if (table_build.get_value() == build_set.get_value())
                        {
                            table_build.extend(build_set);

                            possible_builds.push_back(table_build);
                        }
                    }
                }
            }

            // Find all compund builds
            for (Set loose_set : table_loose_sets)
            {
                if (count_cards_held(loose_set.get_value() + player_card.get_value()) > 0)
                {
                    Set build_set;
                    build_set.add_card(player_card);
                    build_set.add_set(loose_set);

                    // Find possible extended builds
                    for (Build table_build : a_table.get_builds())
                    {
                        if (table_build.get_value() == build_set.get_value())
                        {
                            table_build.extend(build_set);

                            possible_builds.push_back(table_build);
                        }
                    }
                }
            }
        }
    }

    // Find best build
    Build best_build;

    for (Build build : possible_builds)
    {
        if (build.get_weight() > best_build.get_weight())
        {
            best_build = build;
        }
    }

    cout << "\nWith " << best_build.get_sets().back().get_first_card().get_name();
    cout << " extend " << best_build.ToString() << endl;
    cout << "Heuristic: " << best_build.get_weight() << endl;

    return best_build;
}

/**********************************************************************
Function Name: find_best_create
Purpose: To find the best new build
Parameters:
    a_table, a Table instace passed by value
Return Value: The best new build, a Build instance
**********************************************************************/
Build Player::find_best_create(Table a_table)
{
    // Find possible builds
    vector<Build> possible_builds;

    Set table_loose_set = a_table.get_loose_set();
    vector<Set> table_loose_sets = generate_set_combinations(table_loose_set);

    for (Card player_card : m_hand.get_cards())
    {
        if (!reserved_for_capture(a_table, player_card))
        {
            // Find all simple builds
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

            // Find all compund builds
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

    // Find best build
    Build best_build;

    for (Build build : possible_builds)
    {
        if (build.get_weight() > best_build.get_weight())
        {
            best_build = build;
        }
    }

    cout << "\nWith " << best_build.get_sets().front().get_first_card().get_name();
    cout << " build " << best_build.ToString() << endl;
    cout << "Heuristic: " << best_build.get_weight() << endl;

    return best_build;
}

/**********************************************************************
Function Name: find_best_caputre
Purpose: To find the best capture set
Parameters:
    a_table, a Table instace passed by value
Return Value: The best capture set, a Set instance
**********************************************************************/
Set Player::find_best_caputre(Table a_table)
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
        Set capture_set;
        capture_set.add_card(player_card);
        capture_set.add_set(matching_loose_cards);
        capture_set.add_set(best_matching_loose_set);

        for (Build build : matching_builds)
        {
            for (Set set : build.get_sets())
            {
                capture_set.add_set(set);
            }
        }

        if (capture_set.get_size() > 1)
        {
            possible_capture_sets.push_back(capture_set);
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
    }

    cout << "\nWith " << best_capture_set.get_first_card().get_name();
    cout << " capture " << best_capture_set.ToString() << endl;
    cout << "Heuristic: " << best_capture_set.get_weight() << endl;

    return best_capture_set;
}

/**********************************************************************
Function Name: find_best_trail
Purpose: To find the best trail card
Parameters:
    a_table, a Table instace passed by value
Return Value: The best trail card, a Card instance
**********************************************************************/
Card Player::find_best_trail(Table a_table)
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

    cout << "\nTrail with " << best_trail_card.get_name() << endl;
    cout << "Heuristic: " << best_trail_card.get_weight() << endl;

    return best_trail_card;
}

/**********************************************************************
Function Name: generate_set_combinations
Purpose: To generate set combinations
Parameters:
    a_loose_set, a Set instace passed by value
Return Value: The possible set combinations, a vector of Set instances
**********************************************************************/
vector<Set> Player::generate_set_combinations(Set a_loose_set)
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

/**********************************************************************
Function Name: vector_contains_set
Purpose: To determine whether a vector of sets contains specified set
Parameters:
    a_vector, a vector of Set instances passed by value
    a_set, a Set instace passed by value
Return Value: The possible set combinations, a vector of Set instances
**********************************************************************/
bool Player::vector_contains_set(vector<Set> a_vector, Set a_set)
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
