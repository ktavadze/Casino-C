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
    virtual void play(Table & a_table);
    virtual void capture_card(Card a_card);
    string ToString();
protected:
    bool m_is_human;
    int m_score;
    Set m_hand;
    Set m_pile;

    virtual bool make_move(Table & a_table);
    virtual bool build_move(Table & a_table);
    virtual bool create_build(Table & a_table);
    virtual bool increase_build(Table & a_table);
    virtual bool extend_build(Table & a_table);
    virtual bool capture_move(Table & a_table);
    virtual bool trail_move(Table & a_table);
    virtual bool can_play(Card a_card, Table a_table);
    virtual bool holds_card_of_value(int a_value);
};
