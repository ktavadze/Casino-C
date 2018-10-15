#pragma once

#include "Player.h"

using namespace std;

class Computer : public Player
{
public:
    Computer()
    {
        m_is_human = false;
    }
    Computer(bool a_is_next, int a_score, Set a_hand, Set a_pile)
    {
        m_is_human = false;
        m_is_next = a_is_next;
        m_score = a_score;
        m_hand = a_hand;
        m_pile = a_pile;
    }
    virtual int make_move(Table & a_table);
private:
    bool can_capture(Table a_table);
    vector<Set> generate_loose_sets(Set a_loose_set);
    bool vector_contains_set(vector<Set> a_vector, Set a_set);
};
