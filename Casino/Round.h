#pragma once

#include "Deck.h"

using namespace std;

class Round
{
public:
    Round() {}
    Round(int a_number)
    {
        m_number = a_number;
    }
    Round(int a_number, Table a_table, Deck a_deck)
    {
        m_number = a_number;
        m_table = a_table;
        m_deck = a_deck;
    }
    inline int get_number()
    {
        return m_number;
    }
    void start(Player & a_computer, Player & a_human);
    string ToString(Player a_computer, Player a_human);
private:
    int m_number;
    Table m_table;
    Deck m_deck;

    bool is_over(Player a_computer, Player a_human);
    void start_turn(Player & a_computer, Player & a_human);
    bool make_move(Player & a_computer, Player & a_human);
    void update_scores(Player & a_computer, Player & a_human);
};
