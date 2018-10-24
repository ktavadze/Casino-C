#pragma once

using namespace std;

class Tournament
{
public:
    Tournament() {}
    Tournament(bool a_human_turn)
    {
        m_computer.is_next(!a_human_turn);
        m_human.is_next(a_human_turn);
        m_round = Round(1);
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
