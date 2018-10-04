#include "pch.h"
#include "Tournament.h"

void Tournament::start()
{
    while (!is_over())
    {
        m_round.start();

        Console::display_tournament_scores(m_computer.get_score(), m_human.get_score());
    }

    Console::display_tournament_result(m_computer.get_score(), m_human.get_score());
}

bool Tournament::is_over()
{
    if (m_computer.get_score() >= 21 || m_human.get_score() >= 21)
    {
        return true;
    }

    return false;
}
