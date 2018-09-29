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
};
