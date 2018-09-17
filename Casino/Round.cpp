#include "pch.h"
#include "Round.h"

using namespace std;

void Round::Start(Computer& a_computer, Human& a_human, bool a_human_first)
{
    vector<Card> hand;
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.Draw();
        hand.push_back(m_deck.Draw());
    }
    a_human.set_hand(hand);

    hand.clear();
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.Draw();
        hand.push_back(m_deck.Draw());
    }
    a_computer.set_hand(hand);

    hand.clear();
    for (int i = 0; i < 4; i++)
    {
        Card card = m_deck.Draw();
        hand.push_back(m_deck.Draw());
    }
    m_table = hand;

    hand = a_computer.get_hand();
    cout << endl << "Computer" << endl;
    for (int i = 0; i < 4; i++)
    {
        Card card = hand.at(i);
        cout << card.get_suit() << card.get_value() << "\t";
    }

    hand = a_human.get_hand();
    cout << endl << "Human" << endl;
    for (int i = 0; i < 4; i++)
    {
        Card card = hand.at(i);
        cout << card.get_suit() << card.get_value() << "\t";
    }

    cout << endl << "Table" << endl;
    for (int i = 0; i < 4; i++)
    {
        Card card = m_table.at(i);
        cout << card.get_suit() << card.get_value() << "\t";
    }
}
