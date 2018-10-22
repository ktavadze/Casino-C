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
    void ask_for_help(Table a_table);
private:
    bool process_build(Table & a_table);
    bool process_build_create(Table & a_table);
    bool process_build_increase(Table & a_table);
    bool process_build_extend(Table & a_table);
    bool process_capture(Table & a_table);
    bool process_trail(Table & a_table);
    bool can_create_build(Table a_table, Card a_build_card, Set a_loose_set);
    bool can_increase_build(Table a_table, Build a_selected_build, Card a_build_card);
    bool can_extend_build(Table a_table, Build a_selected_build, Card a_build_card, Set a_loose_set);
    bool can_capture_selection(Table a_table, Card a_capture_card, Set a_loose_set, Set a_firm_set);
    bool can_trail(Table a_table, Card a_trail_card);
    void capture(Table & a_table, Card a_capture_card, Set a_loose_set, Set a_firm_set);
};
