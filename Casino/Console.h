#pragma once

#include "Card.h"
#include "Build.h"

using namespace std;

class Console
{
public:
    static int ProcessMainMenu();
    static bool ProcessCoinToss();
    static int ProcessTurnMenu(bool a_is_human);
    static int ProcessMoveMenu();
    static int ProcessCardPick(vector<Card> a_hand);
    static int ProcessBuildMenu();
    static void DisplayMessage(string a_message);
};
