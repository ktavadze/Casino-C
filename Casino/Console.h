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
    static int ProcessTrailMenu(vector<Card> a_hand);
    static void DisplayMessage(string a_message);
};
