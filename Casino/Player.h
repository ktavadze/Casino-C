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
    virtual void Play(Table & a_table);
    virtual bool MakeMove(Table & a_table);
    virtual bool TrailMove(Table & a_table);
    virtual bool BuildMove(Table & a_table);
    virtual bool CreateBuild(Table & a_table);
    virtual bool CanPlay(Table a_table, Card a_card);
    string ToString();
protected:
    bool m_is_human;
    int m_score;
    Set m_hand;
    Set m_pile;
};
