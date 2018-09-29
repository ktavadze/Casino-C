#pragma once

#include "Round.h"

using namespace std;

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
