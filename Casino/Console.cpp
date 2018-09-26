#include "pch.h"
#include "Console.h"
#include <ctime>

using namespace std;

int Console::ProcessMainMenu()
{
    cout << "Welcome to Casino!" << endl;

    int choice;
    do
    {
        cout << endl << "Main menu" << endl;
        cout << "1. Start a new game" << endl;
        cout << "2. Load an old game" << endl;
        cout << "3. Quit the game" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice != 1 && choice != 2 && choice != 3);

    return choice;
}

bool Console::ProcessCoinToss()
{
    int choice;
    do
    {
        cout << endl << "Coin toss" << endl;
        cout << "1. Guess heads" << endl;
        cout << "2. Guess tails" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice != 1 && choice != 2);

    srand(time(NULL));
    int coin = rand() % 2 + 1;

    string result;
    if (coin == 1)
    {
        result = "Heads";
    }
    else
    {
        result = "Tails";
    }
    cout << endl << "Result" << endl;
    cout << coin << ". " << result << endl;

    if (choice == coin)
    {
        return true;
    }

    return false;
}

int Console::ProcessTurnMenu()
{
    int choice;
    do
    {
        cout << endl << "Turn menu" << endl;
        cout << "1. Save the game" << endl;
        cout << "2. Make a move" << endl;
        cout << "3. Quit the game" << endl;
        cin >> choice;
    } while (choice != 1 && choice != 2 && choice != 3);

    return choice;
}

int Console::ProcessMoveMenu()
{
    int choice;
    do
    {
        cout << endl << "Move menu" << endl;
        cout << "1. Build" << endl;
        cout << "2. Capture" << endl;
        cout << "3. Trail" << endl;
        cin >> choice;
    } while (choice != 1 && choice != 2 && choice != 3);

    return choice;
}

int Console::ProcessTrailMenu(int a_size)
{
    int index;
    do
    {
        cout << endl << "Card index: ";
        cin >> index;
    } while (index < 0 || index >= a_size);

    return index;
}

void Console::DisplayMessage(string a_message)
{
    cout << a_message << endl;
}
