#pragma once

#include "Human.h"
#include "Computer.h"
#include "Round.h"
#include <vector>

class Tournament
{
public:
    Tournament() {}
    void Start();
    void Load() {}
private:
    Human m_human;
    Computer m_computer;
    Round m_round;
};
