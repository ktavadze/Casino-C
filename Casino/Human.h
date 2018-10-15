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
private:
    bool process_build(Table & a_table);
    bool process_build_create(Table & a_table);
    bool process_build_increase(Table & a_table);
    bool process_build_extend(Table & a_table);
    bool process_capture(Table & a_table);
    bool process_trail(Table & a_table);
};
