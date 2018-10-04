#include "pch.h"
#include "Console.h"
#include <ctime>
#include <algorithm>

int Console::process_main_menu()
{
    cout << "***WELCOME TO CASINO!***" << endl;

    int choice;
    do
    {
        cout << endl << "***MAIN MENU***" << endl;
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
        cout << endl << "***COIN TOSS***" << endl;
        cout << "1. Guess heads" << endl;
        cout << "2. Guess tails" << endl;

        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice != 1 && choice != 2);

    // Flip coin
    srand((unsigned int)time(NULL));
    int coin = rand() % 2 + 1;

    // Display result
    cout << endl << "RESULT: ";
    if (coin == 1)
    {
        cout << "heads";
    }
    else
    {
        cout << "tails";
    }

    cout << " - ";
    if (coin == choice)
    {
        cout << "correct!" << endl;

        return true;
    }

    cout << "incorrect!" << endl;

    return false;
}

int Console::process_turn_menu(bool a_is_human)
{
    int choice;
    if (a_is_human)
    {
        do
        {
            cout << endl << "***HUMAN TURN MENU***" << endl;
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
            cout << endl << "***COMPUTER TURN MENU***" << endl;
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
        cout << endl << "***MOVE MENU***" << endl;
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
        cout << endl << "***BUILD MENU***" << endl;
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
    int size = a_hand.get_size();

    int choice;
    do
    {
        cout << endl << "Pick card:" << endl;

        Card card;
        for (int i = 0; i < size; i++)
        {
            card = a_hand.get_card(i);

            cout << i + 1 << ". " << card.get_name() << endl;
        }

        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice < 1 || choice > size);

    return choice;
}

int Console::pick_build(vector<Build> a_builds)
{
    int size = a_builds.size();

    int choice;
    do
    {
        cout << endl << "Pick build:" << endl;

        Build build;
        for (int i = 0; i < size; i++)
        {
            build = a_builds.at(i);

            cout << i + 1 << ". " << build.ToString() << endl;
        }

        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice < 1 || choice > size);

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

        string input;
        getline(cin, input, '\n');

        // Normalize
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

Set Console::pick_table_set(Table a_table)
{
    Set selected_set;

    bool do_again;
    do
    {
        selected_set.reset();

        do_again = false;

        cout << endl << "Pick card(s): " << a_table.ToString() << endl;

        string input;
        getline(cin, input, '\n');

        // Normalize
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
    cout << endl << a_message << endl;
}

void Console::display_round_scores(int a_computer_score, int a_human_score)
{
    cout << endl << "***ROUND SCORES***" << endl;
    cout << "Computer: " << a_computer_score << endl;
    cout << "Human: " << a_human_score << endl;
}

void Console::display_tournament_scores(int a_computer_score, int a_human_score)
{
    cout << endl << "***TOURNAMENT SCORES***" << endl;
    cout << "Computer: " << a_computer_score << endl;
    cout << "Human: " << a_human_score << endl;
}

void Console::display_tournament_result(int a_computer_score, int a_human_score)
{
    cout << endl << "RESULT: ";
    if (a_computer_score > a_human_score)
    {
        cout << "computer wins!";
    }
    else if (a_computer_score < a_human_score)
    {
        cout << "human wins!";
    }
    else
    {
        cout << "it's a tie!";
    }
    cout << endl;
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
