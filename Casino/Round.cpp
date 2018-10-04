#include "pch.h"
#include "Round.h"

Round::Round(Computer * a_computer, Human * a_human)
{
    m_number = 1;

    m_computer = a_computer;
    m_human = a_human;

    deal_players();

    // Deal table
    m_table.set_loose_set(m_deck.draw_set());

    m_human_next = Console::process_coin_toss();
}

void Round::start()
{
    while (!is_over())
    {
        Console::display_message(ToString());

        if (m_human_next)
        {
            m_human->play(m_table);
            m_human_next = false;
        }
        else
        {
            m_computer->play(m_table);
            m_human_next = true;
        }

        if (m_computer->get_hand().get_size() == 0 && m_human->get_hand().get_size() == 0)
        {
            deal_players();
        }
    }

    clear_table();

    update_scores();
}

string Round::ToString()
{
    string info;

    info += "Round: " + to_string(m_number) + "\n";

    info += "\nComputer:" + m_computer->ToString() + "\n";

    info += "\nHuman:" + m_human->ToString() + "\n";

    info += "\nTable: " + m_table.ToString() + "\n";

    info += "\nDeck: " + m_deck.ToString() + "\n";

    info += "\nNext Player: ";
    if (m_human_next)
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

void Round::deal_players()
{
    m_human->set_hand(m_deck.draw_set());
    m_computer->set_hand(m_deck.draw_set());
}

void Round::clear_table()
{
    if (m_table.get_loose_set().get_size() > 0)
    {
        for (Card card : m_table.get_loose_set().get_cards())
        {
            if (m_human_last)
            {
                // Add loose card to human pile
                m_human->capture_card(card);
            }
            else
            {
                // Add loose card to computer pile
                m_computer->capture_card(card);
            }

            // Remove loose card from table
            m_table.remove_card(card);
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
