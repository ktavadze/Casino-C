#pragma once

#include "Round.h"

class Tournament
{
public:
    Tournament() {}
    void Start();
private:
    Computer m_computer;
    Human m_human;
    Round m_round;
};
