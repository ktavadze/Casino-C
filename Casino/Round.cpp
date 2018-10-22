#include "pch.h"
#include "Round.h"

void Round::start()
{
    while (!is_over())
    {
        start_turn();

        if (m_computer->get_hand().get_size() == 0 && m_human->get_hand().get_size() == 0)
        {
            // Deal players
            m_human->set_hand(m_deck.draw_set());
            m_computer->set_hand(m_deck.draw_set());
        }
    }

    // Clear table
    if (m_table.get_loose_set().get_size() > 0)
    {
        for (Card card : m_table.get_loose_set().get_cards())
        {
            // Check capture status
            if (m_human->captured_last())
            {
                // Add loose card to human pile
                m_human->add_to_pile(card);
            }
            else
            {
                // Add loose card to computer pile
                m_computer->add_to_pile(card);
            }

            // Remove loose card from table
            m_table.remove_loose_card(card);
        }
    }

    update_scores();

    // Clear piles
    m_human->clear_pile();
    m_computer->clear_pile();
}

string Round::ToString()
{
    string info;

    info += "Round: " + to_string(m_number) + "\n";

    info += "\nComputer:" + m_computer->ToString() + "\n";

    info += "\nHuman:" + m_human->ToString() + "\n";

    info += "\nTable: " + m_table.ToString() + "\n";

    for (Build build : m_table.get_builds())
    {
        info += "\nBuild Owner: " + build.ToString();
        if (build.is_human())
        {
            info += " Human\n";
        }
        else
        {
            info += " Computer\n";
        }
    }

    info += "\nDeck: " + m_deck.ToString() + "\n";

    info += "\nNext Player: ";
    if (m_human->is_next())
    {
        info += "Human";
    }
    else
    {
        info += "Computer";
    }

    return info;
}

bool Round::is_over()
{
    if (m_deck.is_empty())
    {
        if (m_computer->get_hand().get_size() == 0 && m_human->get_hand().get_size() == 0)
        {
            return true;
        }
    }

    return false;
}

void Round::start_turn()
{
    for (;;)
    {
        Console::display_message(ToString());

        int choice = Console::process_turn_menu(m_human->is_next());

        if (m_human->is_next())
        {
            switch (choice)
            {
            case 1:
                Serialization::save_game(ToString());
                break;
            case 2:
                if (make_move())
                {
                    m_human->is_next(false);
                    m_computer->is_next(true);

                    return;
                }
                break;
            case 3:
                m_human->ask_for_help(m_table);
                break;
            case 4:
                exit(0);
            }
        }
        else
        {
            switch (choice)
            {
            case 1:
                Serialization::save_game(ToString());
                break;
            case 2:
                if (make_move())
                {
                    m_human->is_next(true);
                    m_computer->is_next(false);

                    return;
                }
                break;
            case 3:
                exit(0);
            }
        }
    }
}

bool Round::make_move()
{
    if (m_human->is_next())
    {
        int move_code = m_human->make_move(m_table);

        switch (move_code)
        {
        case 1:
            m_human->captured_last(true);
            m_computer->captured_last(false);
        case 0:
            return true;
        default:
            return false;
        }
    }
    else
    {
        int move_code = m_computer->make_move(m_table);

        switch (move_code)
        {
        case 1:
            m_human->captured_last(false);
            m_computer->captured_last(true);
        case 0:
            return true;
        default:
            return false;
        }
    }
}

void Round::update_scores()
{
    int computer_score = 0;
    int human_score = 0;

    Set computer_pile = m_computer->get_pile();
    Set human_pile = m_human->get_pile();

    // Check pile sizes
    if (computer_pile.get_size() > human_pile.get_size())
    {
        computer_score += 3;
    }
    else if (computer_pile.get_size() < human_pile.get_size())
    {
        human_score += 3;
    }

    // Count spades
    int computer_spades = 0;
    int human_spades = 0;

    for (Card card : computer_pile.get_cards())
    {
        if (card.is_spade())
        {
            computer_spades++;
        }
    }

    for (Card card : human_pile.get_cards())
    {
        if (card.is_spade())
        {
            human_spades++;
        }
    }

    // Check spade counts
    if (computer_spades > human_spades)
    {
        computer_score += 1;
    }
    else if (computer_spades < human_spades)
    {
        human_score += 1;
    }

    // Check DX
    Card ten_of_diamonds("DX");

    if (computer_pile.contains(ten_of_diamonds))
    {
        computer_score += 2;
    }
    else if (human_pile.contains(ten_of_diamonds))
    {
        human_score += 2;
    }

    // Check S2
    Card two_of_spades("S2");

    if (computer_pile.contains(two_of_spades))
    {
        computer_score += 1;
    }
    else if (human_pile.contains(two_of_spades))
    {
        human_score += 1;
    }

    // Check aces
    for (Card card : computer_pile.get_cards())
    {
        if (card.is_ace())
        {
            computer_score += 1;
        }
    }

    for (Card card : human_pile.get_cards())
    {
        if (card.is_ace())
        {
            human_score += 1;
        }
    }

    // Update scores
    m_computer->set_score(m_computer->get_score() + computer_score);
    m_human->set_score(m_human->get_score() + human_score);

    Console::display_round_scores(computer_score, human_score);
}
