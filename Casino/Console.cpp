#include "pch.h"
#include "Console.h"
#include <ctime>
#include <algorithm>

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

    srand((unsigned int)time(NULL));
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
            cout << endl << "Human turn menu" << endl;
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
            cout << endl << "Computer turn menu" << endl;
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

int Console::PickPlayerCard(Set a_hand)
{
    int choice;
    do
    {
        cout << endl << "Pick card" << endl;

        Card card;
        for (int i = 0; i < a_hand.Size(); i++)
        {
            card = a_hand.Get(i);
            cout << i + 1 << ". " << card.get_name() << endl;
        }

        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice < 1 || choice > a_hand.Size());

    return choice;
}

Set Console::PickLooseCards(Set a_cards)
{
    Set cards;

    bool do_again;
    do
    {
        cards.Clear();

        do_again = false;

        cout << endl << "Pick card(s):" + a_cards.ToString() << endl;

        // Get names
        string input;
        getline(cin, input, '\n');

        // Convert to uppercase
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        // Tokenize
        vector<string> names = StringToVector(input, ' ');

        // Validate
        if (names.empty())
        {
            do_again = true;
        }

        for (string name : names)
        {
            Card card(name);

            if (!a_cards.Contains(card))
            {
                do_again = true;
            }
            else
            {
                cards.AddCard(card);
            }
        }
    } while (do_again);

    return cards;
}

Set Console::PickTableCards(Table a_table)
{
    Set cards;

    bool do_again;
    do
    {
        cards.Clear();

        do_again = false;

        cout << endl << "Pick card(s):" << a_table.ToString() << endl;

        // Get names
        string input;
        getline(cin, input, '\n');

        // Convert to uppercase
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        // Tokenize
        vector<string> names = StringToVector(input, ' ');

        // Validate
        if (names.empty())
        {
            do_again = true;
        }

        for (string name : names)
        {
            Card card(name);

            if (!a_table.Contains(card))
            {
                do_again = true;
            }
            else
            {
                cards.AddCard(card);
            }
        }
    } while (do_again);

    return cards;
}

void Console::DisplayMessage(string a_message)
{
    cout << a_message << endl;
}

vector<string> Console::StringToVector(string a_string, char a_delimiter)
{
    vector<string> tokens;

    string token;
    for_each(begin(a_string), end(a_string), [&](char const ch)
    {
        if (ch != a_delimiter)
        {
            token += ch;
        }
        else
        {
            if (token.length() > 0)
            {
                tokens.push_back(token);
                token.clear();
            }
        }
    });

    if (token.length() > 0)
    {
        tokens.push_back(token);
    }

    return tokens;
}
