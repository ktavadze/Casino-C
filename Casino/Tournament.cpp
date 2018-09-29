#include "pch.h"
#include "Tournament.h"

void Tournament::Start()
{
    bool human_first = Console::ProcessCoinToss();

    m_round = Round(1, &m_computer, &m_human, human_first);

    m_round.Start();
}
