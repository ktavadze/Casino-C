#include "pch.h"
#include "Human.h"

int Human::make_move(Table & a_table)
{
    int choice = Console::process_move_menu();

    switch (choice)
    {
    case 1:
        if (process_build(a_table))
        {
            return 0;
        }
        break;
    case 2:
        if (process_capture(a_table))
        {
            return 1;
        }
        break;
    case 3:
        if (process_trail(a_table))
        {
            return 0;
        }
        break;
    }

    return -1;
}

bool Human::process_build(Table & a_table)
{
    int choice = Console::process_build_menu();

    switch (choice)
    {
    case 1:
        return process_build_create(a_table);
    case 2:
        return process_build_increase(a_table);
    case 3:
        return process_build_extend(a_table);
    default:
        return false;
    }
}

bool Human::process_build_create(Table & a_table)
{
    // Check loose set
    if (a_table.get_loose_set().get_size() == 0)
    {
        Console::display_message("ERROR: no loose cards to build with!");

        return false;
    }

    // Select build card
    int build_card_index = Console::pick_player_card(m_hand) - 1;
    Card build_card = m_hand.get_card(build_card_index);

    // Select loose set
    Set loose_set = Console::pick_loose_set(a_table.get_loose_set());

    // Create build
    if (can_create_build(a_table, build_card, loose_set))
    {
        Set build_set;

        build_set.add_card(build_card);

        build_set.add_set(loose_set);

        Build build(m_is_human, build_set);

        // Add build to table
        a_table.add_build(build);

        // Remove loose set from table
        for (Card card : loose_set.get_cards())
        {
            a_table.remove_loose_card(card);
        }

        // Remove build card from hand
        m_hand.remove_card(build_card);

        return true;
    }

    return false;
}

bool Human::process_build_increase(Table & a_table)
{
    // Check builds
    if (a_table.get_builds().size() == 0)
    {
        Console::display_message("ERROR: no builds to increase!");

        return false;
    }

    // Select build
    int selected_build_index = Console::pick_build(a_table.get_builds()) - 1;
    Build selected_build = a_table.get_builds().at(selected_build_index);

    // Select build card
    int build_card_index = Console::pick_player_card(m_hand) - 1;
    Card build_card = m_hand.get_card(build_card_index);

    // Increase build
    if (can_increase_build(a_table, selected_build, build_card))
    {
        Set build_set;

        build_set.add_card(build_card);

        for (Set set : selected_build.get_sets())
        {
            build_set.add_set(set);
        }

        Build increased_build(m_is_human, build_set);

        // Add increased build to table
        a_table.add_build(increased_build);

        // Remove selected build from table
        a_table.remove_build(selected_build);

        // Remove build card from hand
        m_hand.remove_card(build_card);

        return true;
    }

    return false;
}

bool Human::process_build_extend(Table & a_table)
{
    // Check builds
    if (a_table.get_builds().size() == 0)
    {
        Console::display_message("ERROR: no builds to extend!");

        return false;
    }

    // Select build
    int selected_build_index = Console::pick_build(a_table.get_builds()) - 1;
    Build selected_build = a_table.get_builds().at(selected_build_index);

    // Select build card
    int build_card_index = Console::pick_player_card(m_hand) - 1;
    Card build_card = m_hand.get_card(build_card_index);

    // Select loose set
    Set loose_set;

    if (selected_build.get_value() != build_card.get_value())
    {
        loose_set = Console::pick_loose_set(a_table.get_loose_set());
    }

    if (can_extend_build(a_table, selected_build, build_card, loose_set))
    {
        Set build_set;

        build_set.add_card(build_card);

        build_set.add_set(loose_set);

        // Update build owner
        a_table.update_build_owner(selected_build_index, m_is_human);

        // Extend build
        a_table.extend_build(selected_build_index, build_set);

        // Remove loose set from table
        if (build_set.get_size() > 1)
        {
            for (int i = 1; i < build_set.get_size(); i++)
            {
                Card card = build_set.get_card(i);

                a_table.remove_loose_card(card);
            }
        }

        // Remove build card from hand
        m_hand.remove_card(build_card);

        return true;
    }

    return false;
}

bool Human::process_capture(Table & a_table)
{
    // Check table
    if (a_table.get_builds().empty() && a_table.get_loose_set().get_size() == 0)
    {
        Console::display_message("ERROR: no cards to capture!");

        return false;
    }

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

bool Human::process_trail(Table & a_table)
{
    // Select trail card
    int trail_card_index = Console::pick_player_card(m_hand) - 1;
    Card trail_card = m_hand.get_card(trail_card_index);

    if (can_trail(a_table, trail_card))
    {
        // Add trail card to table
        a_table.add_loose_card(trail_card);

        // Remove trail card from hand
        m_hand.remove_card(trail_card);

        return true;
    }

    return false;
}
