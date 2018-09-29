#include "pch.h"
#include "Console.h"
#include <ctime>

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
    } while (choice < 1 || choice > 3);

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
    cout << endl << "Result: " << result << endl;

    if (choice == coin)
    {
        cout << "You guessed RIGHT" << endl;
        return true;
    }

    cout << "You guessed WRONG" << endl;
    return false;
}

int Console::ProcessTurnMenu(bool a_is_human)
{
    int choice;
    if (a_is_human)
    {
        do
        {
            cout << endl << "Turn menu" << endl;
            cout << "1. Save the game" << endl;
            cout << "2. Make a move" << endl;
            cout << "3. Ask for help" << endl;
            cout << "4. Quit the game" << endl;
            cin >> choice;
            cin.clear();
            cin.ignore(1000, '\n');
        } while (choice < 1 || choice > 4);
    }
    else
    {
        do
        {
            cout << endl << "Turn menu" << endl;
            cout << "1. Save the game" << endl;
            cout << "2. Make a move" << endl;
            cout << "3. Quit the game" << endl;
            cin >> choice;
            cin.clear();
            cin.ignore(1000, '\n');
        } while (choice < 1 || choice > 3);
    }

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
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice < 1 || choice > 3);

    return choice;
}

int Console::ProcessCardPick(vector<Card> a_hand)
{
    int size = a_hand.size();

    int choice;
    do
    {
        cout << endl << "Card pick" << endl;

        Card card;
        for (int i = 0; i < size; i++)
        {
            card = a_hand[i];
            cout << i + 1 << ". " << card.get_name() << endl;
        }

        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice < 1 || choice > size);

    return choice;
}

int Console::ProcessBuildMenu()
{
    int choice;
    do
    {
        cout << endl << "Build menu" << endl;
        cout << "1. Create" << endl;
        cout << "2. Increase" << endl;
        cout << "3. Extend" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice < 1 || choice > 3);

    return choice;
}

void Console::DisplayMessage(string a_message)
{
    cout << a_message << endl;
}
