#pragma once

#include "Card.h"
#include "Build.h"

class Console
{
public:
    static int ProcessMainMenu();
    static bool ProcessCoinToss();
    static int ProcessHumanTurnMenu();
    static int ProcessComputerTurnMenu();
    static int ProcessMoveMenu();
    static int ProcessTrailMenu(std::vector<Card> a_hand);
    static void DisplayMessage(std::string a_message);
};
