#include "pch.h"
#include "Player.h"

bool Player::build(Table & a_table)
{
    int choice = Console::process_build_menu();

    switch (choice)
    {
    case 1:
        return create_build(a_table);
    case 2:
        return increase_build(a_table);
    case 3:
        return extend_build(a_table);
    default:
        return false;
    }
}

bool Player::capture(Table & a_table)
{
    // Select player card
    int player_card_index = Console::pick_player_card(m_hand) - 1;
    Card player_card = m_hand.get_card(player_card_index);

    // Select table set
    Set table_set = Console::pick_table_set(a_table);

    // Classify
    Set loose_set;
    Set firm_set;

    for (Card card : table_set.get_cards())
    {
        if (a_table.get_loose_set().contains(card))
        {
            loose_set.add_card(card);
        }
        else
        {
            firm_set.add_card(card);
        }
    }

    // Capture
    if (can_capture(a_table, player_card, loose_set, firm_set))
    {
        // Capture firm set
        for (Build build : a_table.get_builds())
        {
            if (firm_set.contains(build.get_sets()))
            {
                // Add build to pile
                for (Set set : build.get_sets())
                {
                    m_pile.add_set(set);
                }

                // Remove build from table
                a_table.remove_build(build);
            }
        }

        // Capture loose set
        for (Card card : loose_set.get_cards())
        {
            // Add loose card to pile
            m_pile.add_card(card);

            // Remove loose card from table
            a_table.remove_loose_card(card);
        }

        // Add player card to pile
        m_pile.add_card(player_card);

        // Remove player card from hand
        m_hand.remove_card(player_card);

        return true;
    }

    return false;
}

bool Player::trail(Table & a_table)
{
    // Select player card
    int player_card_index = Console::pick_player_card(m_hand) - 1;
    Card player_card = m_hand.get_card(player_card_index);

    // Check player card
    if (!can_play(a_table, player_card))
    {
        Console::display_message("ERROR: selected card reserved for capture!");

        return false;
    }

    // Check loose set
    for (Card card : a_table.get_loose_set().get_cards())
    {
        if (card.get_value() == player_card.get_value())
        {
            Console::display_message("ERROR: must capture matching loose card(s)!");

            return false;
        }
    }

    // Check builds
    for (Build build : a_table.get_builds())
    {
        if (build.is_human() == m_is_human)
        {
            Console::display_message("ERROR: cannot trail while owner of build(s)!");

            return false;
        }
    }

    // Add player card to table
    a_table.add_loose_card(player_card);

    // Remove player card from hand
    m_hand.remove_card(player_card);

    return true;
}

string Player::ToString()
{
    string info;

    info += "\n   Score: " + m_score;

    info += "\n   Hand: " + m_hand.ToString();

    info += "\n   Pile: " + m_pile.ToString();

    return info;
}

bool Player::create_build(Table & a_table)
{
    // Check loose set
    if (a_table.get_loose_set().get_size() == 0)
    {
        Console::display_message("ERROR: no loose cards to build with!");

        return false;
    }

    Set selected_set;

    // Select player card
    int player_card_index = Console::pick_player_card(m_hand) - 1;
    Card player_card = m_hand.get_card(player_card_index);

    // Check player card
    if (can_play(a_table, player_card))
    {
        selected_set.add_card(player_card);
    }
    else
    {
        Console::display_message("ERROR: selected card reserved for capture!");

        return false;
    }

    // Select loose set
    Set loose_set = Console::pick_loose_set(a_table.get_loose_set());

    for (Card card : loose_set.get_cards())
    {
        selected_set.add_card(card);
    }

    Build build(m_is_human, selected_set);

    // Check build value
    if (count_cards_held(build.get_value()) == 0)
    {
        Console::display_message("ERROR: no card in hand matching build value!");

        return false;
    }

    // Add build to table
    a_table.add_build(build);

    // Remove loose set from table
    for (Card loose_card : loose_set.get_cards())
    {
        a_table.remove_loose_card(loose_card);
    }

    // Remove player card from hand
    m_hand.remove_card(player_card);

    return true;
}

bool Player::increase_build(Table & a_table)
{
    // Check builds
    if (a_table.get_builds().size() == 0)
    {
        Console::display_message("ERROR: no builds to increase!");

        return false;
    }

    Set selected_set;

    // Select player card
    int player_card_index = Console::pick_player_card(m_hand) - 1;
    Card player_card = m_hand.get_card(player_card_index);

    // Check player card
    if (can_play(a_table, player_card))
    {
        selected_set.add_card(player_card);
    }
    else
    {
        Console::display_message("ERROR: selected card reserved for capture!");

        return false;
    }

    // Select build
    int selected_build_index = Console::pick_build(a_table.get_builds()) - 1;
    Build selected_build = a_table.get_builds().at(selected_build_index);

    // Check build owner
    if (selected_build.is_human() == m_is_human)
    {
        Console::display_message("ERROR: cannot increase own build!");

        return false;
    }

    // Check build size
    if (selected_build.get_sets().size() > 1)
    {
        Console::display_message("ERROR: cannot increase multi-builds!");

        return false;
    }

    for (Set set : selected_build.get_sets())
    {
        for (Card card : set.get_cards())
        {
            selected_set.add_card(card);
        }
    }

    Build increased_build(m_is_human, selected_set);

    // Check build value
    if (count_cards_held(increased_build.get_value()) == 0)
    {
        Console::display_message("ERROR: no card in hand matching build value!");

        return false;
    }

    // Add increased build to table
    a_table.add_build(increased_build);

    // Remove selected build from table
    a_table.remove_build(selected_build);

    // Remove player card from hand
    m_hand.remove_card(player_card);

    return true;
}

bool Player::extend_build(Table & a_table)
{
    // Check builds
    if (a_table.get_builds().size() == 0)
    {
        Console::display_message("ERROR: no builds to extend!");

        return false;
    }

    Set selected_set;

    // Select build
    int selected_build_index = Console::pick_build(a_table.get_builds()) - 1;
    Build selected_build = a_table.get_builds().at(selected_build_index);

    // Select player card
    int player_card_index = Console::pick_player_card(m_hand) - 1;
    Card player_card = m_hand.get_card(player_card_index);

    // Check player card
    if (can_play(a_table, player_card))
    {
        selected_set.add_card(player_card);
    }
    else
    {
        Console::display_message("ERROR: selected card reserved for capture!");

        return false;
    }

    // Select loose set
    if (selected_build.get_value() != player_card.get_value())
    {
        Set loose_set = Console::pick_loose_set(a_table.get_loose_set());

        for (Card card : loose_set.get_cards())
        {
            selected_set.add_card(card);
        }
    }

    // Check build value
    if (selected_build.get_value() != selected_set.get_value())
    {
        Console::display_message("ERROR: selected sum mismatch!");

        return false;
    }

    // Update build owner
    selected_build.is_human(m_is_human);

    // Extend build
    a_table.extend_build(selected_build_index, selected_set);

    // Remove loose set from table
    if (selected_set.get_size() > 1)
    {
        for (int i = 1; i < selected_set.get_size(); i++)
        {
            Card card = selected_set.get_card(i);

            a_table.remove_loose_card(card);
        }
    }

    // Remove player card from hand
    m_hand.remove_card(player_card);

    return true;
}

bool Player::can_play(Table a_table, Card a_card)
{
    for (Build build : a_table.get_builds())
    {
        if (build.get_value() == a_card.get_value() && build.is_human() == m_is_human)
        {
            if (count_cards_held(a_card.get_value()) < 2)
            {
                return false;
            }
        }
    }

    return true;
}

bool Player::can_capture(Table a_table, Card a_capture_card, Set a_loose_set, Set a_firm_set)
{
    // Check loose set
    if (a_loose_set.get_size() > 0)
    {
        Set non_matching_set;

        for (Card card : a_loose_set.get_cards())
        {
            if (card.get_value() != a_capture_card.get_value())
            {
                non_matching_set.add_card(card);
            }
        }

        // Check loose sum
        if (non_matching_set.get_size() > 0)
        {
            if (non_matching_set.get_value() != a_capture_card.get_value())
            {
                Console::display_message("ERROR: cannot capture selected loose card(s)!");

                return false;
            }
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
        int cards_found = 0;

        for (Build build : a_table.get_builds())
        {
            if (a_firm_set.contains(build.get_sets()))
            {
                if (build.get_value() == a_capture_card.get_value())
                {
                    for (Set set : build.get_sets())
                    {
                        cards_found += set.get_size();
                    }
                }
                else
                {
                    Console::display_message("ERROR: cannot capture selected build(s)!");

                    return false;
                }
            }
        }

        if (a_firm_set.get_size() != cards_found)
        {
            Console::display_message("ERROR: cannot capture selected build card(s)!");

            return false;
        }
    }
    else
    {
        for (Build build : a_table.get_builds())
        {
            if (build.get_value() == a_capture_card.get_value() && build.is_human() == m_is_human)
            {
                if (count_cards_held(a_capture_card.get_value()) < 2)
                {
                    Console::display_message("ERROR: must capture matching owned build(s)!");

                    return false;
                }
            }
        }
    }

    return true;
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
