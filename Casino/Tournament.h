#pragma once

#include "Round.h"

using namespace std;

class Tournament
{
public:
    Tournament() {}
    void start();
private:
    Computer m_computer;
    Human m_human;
    Round m_round;
};
