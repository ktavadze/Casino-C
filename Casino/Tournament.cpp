#include "pch.h"
#include "Tournament.h"

void Tournament::start()
{
    while (!is_over())
    {
        m_round.start();

        Console::display_tournament_scores(m_computer.get_score(), m_human.get_score());

        if (!is_over())
        {
            int round_number = m_round.get_number() + 1;
            bool human_turn = m_human.captured_last();

            m_round = Round(round_number, &m_computer, &m_human, human_turn);
        }
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
