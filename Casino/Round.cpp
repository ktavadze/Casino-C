#include "pch.h"
#include "Round.h"

void Round::Start()
{
    DealCards();

    vector<Card> cards;
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.Draw();
        cards.push_back(card);
    }
    m_table.set_cards(cards);

    int turn = 1;
    while (turn <= 48)
    {
        Console::DisplayMessage(ToString());

        if (m_human_next)
        {
            m_human->Play(m_table);
            m_human_next = false;
        }
        else
        {
            m_computer->Play(m_table);
            m_human_next = true;
        }

        if (turn == 48)
        {
            Console::DisplayMessage(ToString());

            break;
        }
        else if (turn % 8 == 0)
        {
            DealCards();
        }

        turn++;
    }
}

void Round::DealCards()
{
    vector<Card> hand;
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.Draw();
        hand.push_back(card);
    }
    m_human->set_hand(hand);

    hand.clear();
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.Draw();
        hand.push_back(card);
    }
    m_computer->set_hand(hand);
}

string Round::ToString()
{
    string info;

    info += "\nRound: " + to_string(m_number) + "\n";

    info += "\nComputer:" + m_computer->ToString() + "\n";

    info += "\nHuman:" + m_human->ToString() + "\n";

    info += "\nTable:" + m_table.ToString() + "\n";

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
