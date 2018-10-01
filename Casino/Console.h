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
    static int PickPlayerCard(vector<Card> a_hand);
    static vector<Card> PickLooseCards(vector<Card> a_cards);
    static vector<Card> PickTableCards(Table a_table);
    static void DisplayMessage(string a_message);
private:
    static vector<string> StringToVector(string a_string, char a_delimiter);
};
