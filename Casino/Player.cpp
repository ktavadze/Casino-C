#include "pch.h"
#include "Player.h"

void Player::play(Table & a_table)
{
    while (true)
    {
        int choice = Console::process_turn_menu(m_is_human);

        if (m_is_human)
        {
            switch (choice)
            {
            case 1:
                // TODO: save game
                exit(0);
            case 2:
                if (make_move(a_table))
                {
                    return;
                }
                break;
            case 3:
                // TODO: ask for help
                exit(0);
            case 4:
                exit(0);
            }
        }
        else
        {
            switch (choice)
            {
            case 1:
                // TODO: save game
                exit(0);
            case 2:
                if (make_move(a_table))
                {
                    return;
                }
                break;
            case 3:
                exit(0);
            }
        }
    }
}

bool Player::make_move(Table & a_table)
{
    int choice = Console::process_move_menu();

    switch (choice)
    {
    case 1:
        return build_move(a_table);
    case 2:
        // TODO: capture
        return false;
    case 3:
        return trail_move(a_table);
    default:
        return false;
    }
}

bool Player::build_move(Table & a_table)
{
    int choice = Console::process_build_menu();

    switch (choice)
    {
    case 1:
        return create_build(a_table);
    case 2:
        return increase_build(a_table);
    case 3:
        // TODO: extend
        return false;
    default:
        return false;
    }
}

bool Player::create_build(Table & a_table)
{
    if (a_table.get_loose_set().get_size() == 0)
    {
        return false;
    }

    Set selected_set;

    // Select player card
    int player_card_index = Console::pick_player_card(m_hand) - 1;
    Card player_card = m_hand.get_card(player_card_index);
    selected_set.add_card(player_card);

    // Select loose set
    Set loose_set = Console::pick_loose_set(a_table.get_loose_set());
    for (Card card : loose_set.get_cards())
    {
        selected_set.add_card(card);
    }

    Build build(m_is_human, selected_set);

    if (holds_card_of_value(build.get_value()))
    {
        if (can_play(a_table, player_card))
        {
            // Update table
            a_table.add_build(build);

            for (Card loose_card : loose_set.get_cards())
            {
                a_table.remove_card(loose_card);
            }

            // Update hand
            m_hand.remove_card(player_card);

            return true;
        }
    }

    return false;
}

bool Player::increase_build(Table & a_table)
{
    if (a_table.get_builds().size() == 0)
    {
        return false;
    }

    Set selected_set;

    // Select player card
    int player_card_index = Console::pick_player_card(m_hand) - 1;
    Card player_card = m_hand.get_card(player_card_index);
    selected_set.add_card(player_card);

    // Select build set
    Set build_set = Console::pick_build_set(a_table);
    for (Card card : build_set.get_cards())
    {
        selected_set.add_card(card);
    }

    Build selected_build(!m_is_human, build_set);

    if (a_table.contains(selected_build))
    {
        Build increased_build(m_is_human, selected_set);

        if (holds_card_of_value(increased_build.get_value()))
        {
            // Update table
            a_table.add_build(increased_build);

            a_table.remove_build(selected_build);

            // Update hand
            m_hand.remove_card(player_card);

            return true;
        }
    }

    return false;
}

bool Player::trail_move(Table & a_table)
{
    int index = Console::pick_player_card(m_hand) - 1;
    Card card = m_hand.get_card(index);

    if (can_play(a_table, card))
    {
        a_table.add_card(card);

        m_hand.remove_card(card);

        return true;
    }

    return false;
}

bool Player::can_play(Table a_table, Card a_card)
{
    for (Build build : a_table.get_builds())
    {
        if (build.get_value() == a_card.get_value() && build.is_human() == m_is_human)
        {
            int count = 0;

            for (Card card : m_hand.get_cards())
            {
                if (card.get_value() == a_card.get_value())
                {
                    count++;
                }
            }

            if (count < 2)
            {
                return false;
            }
        }
    }

    return true;
}

bool Player::holds_card_of_value(int a_value)
{
    for (Card card : m_hand.get_cards())
    {
        if (card.get_value() == a_value)
        {
            return true;
        }
    }

    return false;
}

string Player::ToString()
{
    string info;

    info += "\n    Score: " + m_score;

    info += "\n    Hand: " + m_hand.ToString();

    info += "\n    Pile: " + m_pile.ToString();

    return info;
}
