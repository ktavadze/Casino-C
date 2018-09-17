#pragma once

#include "Card.h"
#include <vector>
#include <stack>

class Player
{
public:
    Player() {}
    inline int score()
    {
        return m_score;
    }
private:
    int m_score;
    std::vector<Card> m_hand;
    std::stack<Card> m_pile;
};
