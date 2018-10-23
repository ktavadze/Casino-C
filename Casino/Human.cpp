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

void Human::ask_for_help(Table a_table)
{
    if (can_increase(a_table))
    {
        find_best_increase(a_table);
    }
    else if (can_extend(a_table))
    {
        find_best_extend(a_table);
    }
    else if (can_build(a_table))
    {
        find_best_build(a_table);
    }
    else if (can_capture(a_table))
    {
        find_best_capture_set(a_table);
    }
    else {
        find_best_trail_card(a_table);
    }
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

        a_table.add_build(build);

        // Remove loose set from table
        a_table.remove_loose_set(loose_set);

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
        a_table.increase_build(build_card_index, build_card, m_is_human);

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

        a_table.extend_build(selected_build_index, build_set, m_is_human);

        // Remove loose set from table
        a_table.remove_loose_set(loose_set);

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

    // Select capture card
    int capture_card_index = Console::pick_player_card(m_hand) - 1;
    Card capture_card = m_hand.get_card(capture_card_index);

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
    if (can_capture_selection(a_table, capture_card, loose_set, firm_set))
    {
        capture(a_table, capture_card, loose_set, firm_set);

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

bool Human::can_create_build(Table a_table, Card a_build_card, Set a_loose_set)
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

bool Human::can_increase_build(Table a_table, Build a_selected_build, Card a_build_card)
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

bool Human::can_extend_build(Table a_table, Build a_selected_build, Card a_build_card, Set a_loose_set)
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

bool Human::can_capture_selection(Table a_table, Card a_capture_card, Set a_loose_set, Set a_firm_set)
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
        int cards_found = 0;

        for (Build build : a_table.get_builds())
        {
            if (build.get_value() == a_capture_card.get_value())
            {
                if (build.is_human() == m_is_human && !a_firm_set.contains(build.get_sets()))
                {
                    if (count_cards_held(a_capture_card.get_value()) < 2)
                    {
                        Console::display_message("ERROR: must capture matching owned build(s)!");

                        return false;
                    }
                }

                if (a_firm_set.contains(build.get_sets()))
                {
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

bool Human::can_trail(Table a_table, Card a_trail_card)
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

void Human::capture(Table & a_table, Card a_capture_card, Set a_loose_set, Set a_firm_set)
{
    // Add capture card to pile
    m_pile.add_card(a_capture_card);

    // Remove capture card from hand
    m_hand.remove_card(a_capture_card);

    // Capture loose set
    for (Card card : a_loose_set.get_cards())
    {
        capture_loose_card(a_table, card);
    }

    // Capture firm set
    for (Build build : a_table.get_builds())
    {
        if (a_firm_set.contains(build.get_sets()))
        {
            capture_build(a_table, build);
        }
    }
}
