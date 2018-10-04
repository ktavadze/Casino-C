#pragma once

#include "Computer.h"
#include "Human.h"
#include "Deck.h"

using namespace std;

class Round
{
public:
    Round() {}
    Round(Computer * a_computer, Human * a_human)
    {
        m_number = 1;
        m_computer = a_computer;
        m_human = a_human;

        m_human->set_hand(m_deck.draw_set());
        m_computer->set_hand(m_deck.draw_set());

        m_table.set_loose_set(m_deck.draw_set());

        m_human_next = Console::process_coin_toss();
    }
    Round(int a_number, Computer * a_computer, Human * a_human,
        Table a_table, Deck a_deck, bool a_human_next)
    {
        m_number = a_number;
        m_computer = a_computer;
        m_human = a_human;
        m_table = a_table;
        m_deck = a_deck;
        m_human_next = a_human_next;
    }
    void start();
    string ToString();
private:
    int m_number;
    Computer * m_computer;
    Human * m_human;
    Table m_table;
    Deck m_deck;
    bool m_human_next;

    bool is_over();
    void update_scores();
};
