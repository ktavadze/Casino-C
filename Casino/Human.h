#pragma once

#include "Player.h"

using namespace std;

class Human : public Player
{
public:
    Human()
    {
        m_is_human = true;
    }
    Human(bool a_is_next, int a_score, Set a_hand, Set a_pile)
    {
        m_is_human = true;
        m_is_next = a_is_next;
        m_score = a_score;
        m_hand = a_hand;
        m_pile = a_pile;
    }
    virtual int make_move(Table & a_table);
    bool build(Table & a_table);
    bool capture(Table & a_table);
    bool trail(Table & a_table);
private:
    bool create_build(Table & a_table);
    bool increase_build(Table & a_table);
    bool extend_build(Table & a_table);
};
