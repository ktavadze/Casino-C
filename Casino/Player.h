#pragma once

#include "Card.h"
#include "Table.h"
#include <vector>
#include <stack>

class Player
{
public:
    Player() {}
    inline int get_score()
    {
        return m_score;
    }
    inline void set_score(int a_score)
    {
        m_score = a_score;
    }
    inline std::vector<Card> get_hand()
    {
        return m_hand;
    }
    inline void set_hand(std::vector<Card> a_hand)
    {
        m_hand = a_hand;
    }
    inline std::vector<Card> get_pile()
    {
        return m_pile;
    }
    inline void set_pile(std::vector<Card> a_pile)
    {
        m_pile = a_pile;
    }
    void Play(Table& a_table);
    bool MakeMove(Table& a_table);
    bool Trail(Table& a_table);
    std::string ToString();
private:
    int m_score;
    std::vector<Card> m_hand;
    std::vector<Card> m_pile;
};
