#pragma once

#include "Computer.h"
#include "Human.h"
#include "Deck.h"

using namespace std;

class Round
{
public:
    Round() {}
    Round(Computer * a_computer, Human * a_human);
    Round(int a_number, Computer * a_computer, Human * a_human,
        Table a_table, Deck a_deck, bool a_human_turn)
    {
        m_number = a_number;
        m_computer = a_computer;
        m_human = a_human;
        m_table = a_table;
        m_deck = a_deck;
        m_human_turn = a_human_turn;
    }
    void start();
    string ToString();
private:
    int m_number;
    Computer * m_computer;
    Human * m_human;
    Table m_table;
    Deck m_deck;
    bool m_human_turn;

    bool is_over();
    void play_turn();
    bool make_move();
    void clear_table();
    void update_scores();
};
