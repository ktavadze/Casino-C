#pragma once

#include "Card.h"
#include "Set.h"
#include "Build.h"
#include "Table.h"

using namespace std;

class Console
{
public:
    static int ProcessMainMenu();
    static bool ProcessCoinToss();
    static int ProcessTurnMenu(bool a_is_human);
    static int ProcessMoveMenu();
    static int ProcessBuildMenu();
    static int PickPlayerCard(Set a_hand);
    static Set PickLooseCards(Set a_cards);
    static Set PickTableCards(Table a_table);
    static void DisplayMessage(string a_message);
private:
    static vector<string> StringToVector(string a_string, char a_delimiter);
};
