#include "pch.h"
#include "Tournament.h"

/**********************************************************************
Function Name: start
Purpose: To start the tournament
**********************************************************************/
void Tournament::start()
{
    while (!is_over())
    {
        m_round.start(m_computer, m_human);

        Console::display_tournament_scores(m_computer.get_score(), m_human.get_score());

        if (!is_over())
        {
            int round_number = m_round.get_number() + 1;

            if (m_human.captured_last())
            {
                m_human.is_next(true);
                m_computer.is_next(false);
            }
            else
            {
                m_human.is_next(false);
                m_computer.is_next(true);
            }

            m_round = Round(round_number);
        }
    }

    Console::display_tournament_result(m_computer.get_score(), m_human.get_score());
}

/**********************************************************************
Function Name: is_over
Purpose: To determine whether the tournament is over
Return Value: Whether the tournament is over, a boolean value
**********************************************************************/
bool Tournament::is_over()
{
    if (m_computer.get_score() >= 21 || m_human.get_score() >= 21)
    {
        return true;
    }

    return false;
}
