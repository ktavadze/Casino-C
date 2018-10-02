#include "pch.h"
#include "Console.h"
#include <ctime>
#include <algorithm>

int Console::process_main_menu()
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

bool Console::process_coin_toss()
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

int Console::process_turn_menu(bool a_is_human)
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

int Console::process_move_menu()
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

int Console::process_build_menu()
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

int Console::pick_player_card(Set a_hand)
{
    int choice;
    do
    {
        cout << endl << "Pick card" << endl;

        Card card;
        for (int i = 0; i < a_hand.get_size(); i++)
        {
            card = a_hand.get_card(i);
            cout << i + 1 << ". " << card.get_name() << endl;
        }

        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice < 1 || choice > a_hand.get_size());

    return choice;
}

Set Console::pick_loose_set(Set a_set)
{
    Set selected_set;

    bool do_again;
    do
    {
        selected_set.reset();

        do_again = false;

        cout << endl << "Pick card(s): " + a_set.ToString() << endl;

        // Get names
        string input;
        getline(cin, input, '\n');

        // Convert to uppercase
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        // Tokenize
        vector<string> names = string_to_vector(input, ' ');

        // Validate
        if (names.empty())
        {
            do_again = true;
        }

        for (string name : names)
        {
            Card card(name);
            selected_set.add_card(card);
        }

        for (Card card : selected_set.get_cards())
        {
            if (!a_set.contains(card))
            {
                do_again = true;
            }
        }
    } while (do_again);

    return selected_set;
}

Set Console::pick_build_set(Table a_table)
{
    Set selected_set;

    bool do_again;
    do
    {
        selected_set.reset();

        do_again = false;

        cout << endl << "Pick card(s): ";
        int count = 0;
        for (Build build : a_table.get_builds())
        {
            count++;
            if (count > 1)
            {
                cout << " ";
            }
            cout << build.ToString();
        }
        cout << endl;

        // Get names
        string input;
        getline(cin, input, '\n');

        // Convert to uppercase
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        // Tokenize
        vector<string> names = string_to_vector(input, ' ');

        // Validate
        if (names.empty())
        {
            do_again = true;
        }

        for (string name : names)
        {
            Card card(name);
            selected_set.add_card(card);
        }

        Build human_build(true, selected_set);
        Build computer_build(false, selected_set);
        if (!a_table.contains(human_build) && !a_table.contains(computer_build))
        {
            do_again = true;
        }
    } while (do_again);

    return selected_set;
}

Set Console::pick_table_set(Table a_table)
{
    Set selected_set;

    bool do_again;
    do
    {
        selected_set.reset();

        do_again = false;

        cout << endl << "Pick card(s): " << a_table.ToString() << endl;

        // Get names
        string input;
        getline(cin, input, '\n');

        // Convert to uppercase
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        // Tokenize
        vector<string> names = string_to_vector(input, ' ');

        // Validate
        if (names.empty())
        {
            do_again = true;
        }

        for (string name : names)
        {
            Card card(name);
            selected_set.add_card(card);
        }

        for (Card card : selected_set.get_cards())
        {
            if (!a_table.contains(card))
            {
                do_again = true;
            }
        }
    } while (do_again);

    return selected_set;
}

void Console::display_message(string a_message)
{
    cout << a_message << endl;
}

vector<string> Console::string_to_vector(string a_string, char a_delimiter)
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
