#pragma once

using namespace std;

class Player
{
public:
    Player() {}
    inline bool is_human()
    {
        return m_is_human;
    }
    inline bool is_next()
    {
        return m_is_next;
    }
    inline void is_next(bool a_is_next)
    {
        m_is_next = a_is_next;
    }
    inline bool captured_last()
    {
        return m_captured_last;
    }
    inline void captured_last(bool a_captured_last)
    {
        m_captured_last = a_captured_last;
    }
    inline int get_score()
    {
        return m_score;
    }
    inline void set_score(int a_score)
    {
        m_score = a_score;
    }
    inline Set get_hand()
    {
        return m_hand;
    }
    inline void set_hand(Set a_hand)
    {
        m_hand = a_hand;
    }
    inline Set get_pile()
    {
        return m_pile;
    }
    inline void set_pile(Set a_pile)
    {
        m_pile = a_pile;
    }
    inline void add_to_pile(Card a_card)
    {
        m_pile.add_card(a_card);
    }
    inline void clear_pile()
    {
        m_pile.reset();
    }
    virtual bool build(Table & a_table);
    virtual bool capture(Table & a_table);
    virtual bool trail(Table & a_table);
    string ToString();
protected:
    bool m_is_human;
    bool m_is_next;
    bool m_captured_last;
    int m_score;
    Set m_hand;
    Set m_pile;

    virtual bool create_build(Table & a_table);
    virtual bool increase_build(Table & a_table);
    virtual bool extend_build(Table & a_table);
    virtual bool can_create_build(Table a_table, Card a_build_card, Set a_loose_set);
    virtual bool can_increase_build(Table a_table, Build a_selected_build, Card a_build_card);
    virtual bool can_extend_build(Table a_table, Build a_selected_build, Card a_build_card, Set a_loose_set);
    virtual bool can_capture(Table a_table, Card a_capture_card, Set a_loose_set, Set a_firm_set);
    virtual bool can_trail(Table a_table, Card a_trail_card);
    virtual bool reserved_for_capture(Table a_table, Card a_card);
    virtual bool owns_build(Table a_table);
    virtual int count_cards_held(int a_value);
};
