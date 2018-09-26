#pragma once

class Console
{
public:
    static int ProcessMainMenu();
    static bool ProcessCoinToss();
    static int ProcessTurnMenu();
    static int ProcessMoveMenu();
    static int ProcessTrailMenu(int a_size);
    static void DisplayMessage(std::string a_message);
};
