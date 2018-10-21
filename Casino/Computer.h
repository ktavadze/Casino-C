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
    void process_build(Table & a_table);
    void process_capture(Table & a_table);
    void capture(Table & a_table, Card a_capture_card, Set a_loose_set, vector<Build> a_builds);

    bool can_build(Table a_table);
    bool can_capture(Table a_table);

    bool vector_contains_set(vector<Set> a_vector, Set a_set);
    vector<Set> generate_set_combinations(Set a_set);
};
