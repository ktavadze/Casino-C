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
};
