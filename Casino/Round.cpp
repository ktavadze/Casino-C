#include "pch.h"
#include "Round.h"

using namespace std;

void Round::Start(Computer& a_computer, Human& a_human, bool a_human_first)
{
    m_computer = &a_computer;
    m_human = &a_human;

    DealCards();

    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.Draw();
        m_table.push_back(card);
    }

    m_human_next = a_human_first;

    int turn = 1;
    while (turn <= 48)
    {
        DisplayCards();

        if (m_human_next)
        {
            cout << endl << "Human turn " << turn << endl;
            a_human.Play(m_table);
            m_human_next = false;
        }
        else
        {
            cout << endl << "Computer turn " << turn << endl;
            a_computer.Play(m_table);
            m_human_next = true;
        }

        if (turn == 48)
        {
            DisplayCards();

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
    cout << endl << "Dealing cards..." << endl;

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

    cout << endl << "Cards left: " << m_deck.get_cards().size() << endl;
}

void Round::DisplayCards()
{
    vector<Card> hand = m_computer->get_hand();
    cout << endl << "Computer" << endl;
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        Card card = hand.at(i);
        cout << card.get_suit() << card.get_value() << "\t";
    }

    hand = m_human->get_hand();
    cout << endl << "Human" << endl;
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        Card card = hand.at(i);
        cout << card.get_suit() << card.get_value() << "\t";
    }

    cout << endl << "Table" << endl;
    for (unsigned int i = 0; i < m_table.size(); i++)
    {
        Card card = m_table.at(i);
        cout << card.get_suit() << card.get_value() << "\t";
    }
    cout << endl;
}
