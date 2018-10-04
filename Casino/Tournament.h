#pragma once

#include "Round.h"

using namespace std;

class Tournament
{
public:
    Tournament()
    {
        m_round = Round(&m_computer, &m_human);
    }
    Tournament(Computer a_computer, Human a_human, Round a_round)
    {
        m_computer = a_computer;
        m_human = a_human;
        m_round = a_round;
    }
    void start();
private:
    Computer m_computer;
    Human m_human;
    Round m_round;

    bool is_over();
};
