#pragma once

#include "Card.h"
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
    inline std::stack<Card> get_pile()
    {
        return m_pile;
    }
    inline void set_pile(std::stack<Card> a_pile)
    {
        m_pile = a_pile;
    }
private:
    int m_score;
    std::vector<Card> m_hand;
    std::stack<Card> m_pile;
};
