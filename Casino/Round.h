#pragma once

#include "Computer.h"
#include "Human.h"
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
    inline int get_number() {
        return m_number;
    }
    void start(Computer & a_computer, Human & a_human);
    string ToString(Computer a_computer, Human a_human);
private:
    int m_number;
    Table m_table;
    Deck m_deck;

    bool is_over(Computer a_computer, Human a_human);
    void start_turn(Computer & a_computer, Human & a_human);
    bool make_move(Computer & a_computer, Human & a_human);
    void update_scores(Computer & a_computer, Human & a_human);
};
