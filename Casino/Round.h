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

        m_human_next = Console::process_coin_toss();

        m_human->set_hand(m_deck.draw_set());
        m_computer->set_hand(m_deck.draw_set());

        m_table.set_loose_set(m_deck.draw_set());
    }
    Round(int a_number, Computer * a_computer, Human * a_human,
        bool a_human_next, Table a_table, Deck a_deck)
    {
        m_number = a_number;
        m_computer = a_computer;
        m_human = a_human;
        m_human_next = a_human_next;
        m_table = a_table;
        m_deck = a_deck;
    }
    void start();
    string ToString();
private:
    int m_number;
    Computer * m_computer;
    Human * m_human;
    bool m_human_next;
    Table m_table;
    Deck m_deck;

    bool is_over();
    void update_scores();
};
