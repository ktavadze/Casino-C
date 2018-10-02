#include "pch.h"
#include "Tournament.h"

void Tournament::start()
{
    bool human_first = Console::process_coin_toss();

    m_round = Round(1, &m_computer, &m_human, human_first);

    m_round.start();
}
