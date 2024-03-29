#include "pch.h"
#include "Round.h"

/**********************************************************************
Function Name: start
Purpose: To start the round
Parameters:
    a_computer, a Player instance passed by reference
    a_human, a Player instance passed by reference
**********************************************************************/
void Round::start(Player & a_computer, Player & a_human)
{
    while (!is_over(a_computer, a_human))
    {
        if (a_computer.get_hand().is_empty() && a_human.get_hand().is_empty())
        {
            // Seed deck
            if (a_computer.get_pile().is_empty() && a_human.get_pile().is_empty())
            {
                if (m_table.get_loose_set().is_empty() && m_table.get_builds().empty())
                {
                    if (Console::process_deck_seed())
                    {
                        Serialization::seed_deck(m_deck);
                    }
                }
            }

            // Deal players
            a_human.set_hand(m_deck.draw_set());
            a_computer.set_hand(m_deck.draw_set());

            if (a_computer.get_pile().is_empty() && a_human.get_pile().is_empty())
            {
                if (m_table.get_loose_set().is_empty() && m_table.get_builds().empty())
                {
                    // Deal table
                    m_table.set_loose_set(m_deck.draw_set());
                }
            }
        }

        start_turn(a_computer, a_human);
    }

    // Clear table
    if (m_table.get_loose_set().get_size() > 0)
    {
        for (Card card : m_table.get_loose_set().get_cards())
        {
            // Check capture status
            if (a_human.captured_last())
            {
                // Add loose card to human pile
                a_human.add_to_pile(card);
            }
            else
            {
                // Add loose card to computer pile
                a_computer.add_to_pile(card);
            }

            // Remove loose card from table
            m_table.remove_loose_card(card);
        }
    }

    update_scores(a_computer, a_human);

    // Clear piles
    a_human.clear_pile();
    a_computer.clear_pile();
}

string Round::ToString(Player a_computer, Player a_human)
{
    string info;

    info += "Round: " + to_string(m_number) + "\n";

    info += "\nComputer:" + a_computer.ToString() + "\n";

    info += "\nHuman:" + a_human.ToString() + "\n";

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
    if (a_human.is_next())
    {
        info += "Human";
    }
    else
    {
        info += "Computer";
    }

    return info;
}

/**********************************************************************
Function Name: is_over
Purpose: To determine whether the round is over
Parameters:
    a_computer, a Player instance passed by value
    a_human, a Player instance passed by value
Return Value: Whether the round is over, a boolean value
**********************************************************************/
bool Round::is_over(Player a_computer, Player a_human)
{
    if (m_deck.is_empty())
    {
        if (a_computer.get_hand().is_empty() && a_human.get_hand().is_empty())
        {
            return true;
        }
    }

    return false;
}

/**********************************************************************
Function Name: start_turn
Purpose: To start a turn
Parameters:
    a_computer, a Player instance passed by reference
    a_human, a Player instance passed by reference
**********************************************************************/
void Round::start_turn(Player & a_computer, Player & a_human)
{
    for (;;)
    {
        Console::display_message(ToString(a_computer, a_human));

        int choice = Console::process_turn_menu(a_human.is_next());

        if (a_human.is_next())
        {
            switch (choice)
            {
            case 1:
            {
                string name = Console::process_file_menu();

                string state = ToString(a_computer, a_human);

                if (Serialization::save_game(name, state))
                {
                    exit(0);
                }

                break;
            }
            case 2:
                if (make_move(a_computer, a_human))
                {
                    a_human.is_next(false);
                    a_computer.is_next(true);

                    return;
                }
                break;
            case 3:
                a_human.ask_for_help(m_table);
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
            {
                string name = Console::process_file_menu();

                string state = ToString(a_computer, a_human);

                if (Serialization::save_game(name, state))
                {
                    exit(0);
                }

                break;
            }
            case 2:
                if (make_move(a_computer, a_human))
                {
                    a_human.is_next(true);
                    a_computer.is_next(false);

                    return;
                }
                break;
            case 3:
                exit(0);
            }
        }
    }
}

/**********************************************************************
Function Name: make_move
Purpose: To allow players to make a move
Parameters:
    a_computer, a Player instance passed by reference
    a_human, a Player instance passed by reference
Return Value: Whether a legal move was made, a boolean value
**********************************************************************/
bool Round::make_move(Player & a_computer, Player & a_human)
{
    if (a_human.is_next())
    {
        int move_code = a_human.make_move(m_table);

        switch (move_code)
        {
        case 1:
            a_human.captured_last(true);
            a_computer.captured_last(false);
        case 0:
            return true;
        default:
            return false;
        }
    }
    else
    {
        int move_code = a_computer.make_move(m_table);

        switch (move_code)
        {
        case 1:
            a_human.captured_last(false);
            a_computer.captured_last(true);
        case 0:
            return true;
        default:
            return false;
        }
    }
}

/**********************************************************************
Function Name: update_scores
Purpose: To update player scores
Parameters:
    a_computer, a Player instance passed by reference
    a_human, a Player instance passed by reference
**********************************************************************/
void Round::update_scores(Player & a_computer, Player & a_human)
{
    int computer_score = 0;
    int human_score = 0;

    Set computer_pile = a_computer.get_pile();
    Set human_pile = a_human.get_pile();

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
    a_computer.set_score(a_computer.get_score() + computer_score);
    a_human.set_score(a_human.get_score() + human_score);

    Console::display_round_results(computer_pile, human_pile, computer_spades, human_spades,
        computer_score, human_score);
}
