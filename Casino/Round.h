#pragma once

#include "Computer.h"
#include "Human.h"
#include "Deck.h"

using namespace std;

class Round
{
public:
    Round() {}
    Round(int a_number, Computer * a_computer, Human * a_human)
    {
        m_number = a_number;

        m_computer = a_computer;
        m_human = a_human;

        // Deal players
        m_human->set_hand(m_deck.draw_set());
        m_computer->set_hand(m_deck.draw_set());

        // Deal table
        m_table.set_loose_set(m_deck.draw_set());
    }
    Round(int a_number, Computer * a_computer, Human * a_human,
        Table a_table, Deck a_deck)
    {
        m_number = a_number;
        m_computer = a_computer;
        m_human = a_human;
        m_table = a_table;
        m_deck = a_deck;
    }
    inline int get_number() {
        return m_number;
    }
    void start();
    string ToString();
private:
    int m_number;
    Computer * m_computer;
    Human * m_human;
    Table m_table;
    Deck m_deck;

    bool is_over();
    void play_turn();
    bool make_move();
    void update_scores();
};
