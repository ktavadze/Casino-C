#include "pch.h"
#include "Round.h"

void Round::start()
{
    deal_cards();

    Set cards;
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.draw();
        cards.add_card(card);
    }
    m_table.set_cards(cards);

    int turn = 1;
    while (turn <= 48)
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

        if (turn == 48)
        {
            Console::display_message(ToString());

            break;
        }
        else if (turn % 8 == 0)
        {
            deal_cards();
        }

        turn++;
    }
}

void Round::deal_cards()
{
    Set hand;
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.draw();
        hand.add_card(card);
    }
    m_human->set_hand(hand);

    hand.reset();
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.draw();
        hand.add_card(card);
    }
    m_computer->set_hand(hand);
}

string Round::ToString()
{
    string info;

    info += "\nRound: " + to_string(m_number) + "\n";

    info += "\nComputer:" + m_computer->ToString() + "\n";

    info += "\nHuman:" + m_human->ToString() + "\n";

    info += "\nTable: " + m_table.ToString() + "\n";

    info += "\nDeck:" + m_deck.ToString() + "\n";

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
