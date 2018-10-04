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
    Human(int a_score, Set a_hand, Set a_pile)
    {
        m_is_human = true;
        m_score = a_score;
        m_hand = a_hand;
        m_pile = a_pile;
    }
};
