#include "pch.h"
#include "Console.h"
#include <ctime>
#include <algorithm>

/**********************************************************************
Function Name: process_main_menu
Purpose: To process main menu
Return Value: Menu choice, an integer value
**********************************************************************/
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

/**********************************************************************
Function Name: process_coin_toss
Purpose: To process coin toss
Return Value: Whether the human guessed correctly, a boolean value
**********************************************************************/
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

/**********************************************************************
Function Name: process_deck_seed
Purpose: To process deck seed
Return Value: Whether the human chose to seed deck, a boolean value
**********************************************************************/
bool Console::process_deck_seed()
{
    int choice;

    do
    {
        cout << endl << "***DECK SEED***" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;

        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice != 1 && choice != 2);

    if (choice == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**********************************************************************
Function Name: process_turn_menu
Purpose: To process turn menu
Parameters:
    a_is_human, a boolean
Return Value: Menu choice, an integer value
**********************************************************************/
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

/**********************************************************************
Function Name: process_move_menu
Purpose: To process move menu
Return Value: Menu choice, an integer value
**********************************************************************/
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

/**********************************************************************
Function Name: process_build_menu
Purpose: To process build menu
Return Value: Menu choice, an integer value
**********************************************************************/
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

/**********************************************************************
Function Name: process_file_menu
Purpose: To process file menu
Return Value: File name, a string value
**********************************************************************/
string Console::process_file_menu()
{
    string name;

    cout << endl << "***LOAD MENU***" << endl;
    cout << "Enter file name: ";
    cin >> name;

    return name;
}

/**********************************************************************
Function Name: pick_player_card
Purpose: To pick player card
Parameters:
    a_hand, a Set instance passed by value
Return Value: Menu choice, an integer value
**********************************************************************/
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

/**********************************************************************
Function Name: pick_build
Purpose: To pick build
Parameters:
    a_builds, a vector of Build instances passed by value
Return Value: Menu choice, an integer value
**********************************************************************/
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

/**********************************************************************
Function Name: pick_loose_set
Purpose: To pick loose set
Parameters:
    a_set, a Set instance passed by value
Return Value: Picked loose set, a Set instance
**********************************************************************/
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
        vector<string> names = string_to_vector(input);

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

/**********************************************************************
Function Name: pick_table_set
Purpose: To pick table set
Parameters:
    a_table, a Table instance passed by value
Return Value: Picked set, a Set instance
**********************************************************************/
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
        vector<string> names = string_to_vector(input);

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

/**********************************************************************
Function Name: display_message
Purpose: To display a message
Parameters:
    a_message, a string
**********************************************************************/
void Console::display_message(string a_message)
{
    cout << endl << "**************************************************" << endl;
    cout << a_message;
    cout << endl << "**************************************************" << endl;
}

/**********************************************************************
Function Name: display_round_results
Purpose: To display round results
Parameters:
    a_computer_pile, a Set instance passed by value
    a_human_pile, a Set instance passed by value
    a_computer_spades, an integer
    a_human_spades, an integer
    a_computer_score, an integer
    a_human_score, an integer
**********************************************************************/
void Console::display_round_results(Set a_computer_pile, Set a_human_pile,
    int a_computer_spades, int a_human_spades, int a_computer_score, int a_human_score)
{
    cout << endl << "***ROUND RESULTS***" << endl;
    cout << "Computer: " << endl;
    cout << "   Pile: " << a_computer_pile.ToString() << endl;
    cout << "   Size: " << a_computer_pile.get_size() << endl;
    cout << "   Spades: " << a_computer_spades << endl;
    cout << "   Score: +" << a_computer_score << endl;
    cout << "Human: " << endl;
    cout << "   Pile: " << a_human_pile.ToString() << endl;
    cout << "   Size: " << a_human_pile.get_size() << endl;
    cout << "   Spades: " << a_human_spades << endl;
    cout << "   Score: +" << a_human_score << endl;
}

/**********************************************************************
Function Name: display_tournament_scores
Purpose: To display tournament scores
Parameters:
    a_computer_score, an integer
    a_human_score, an integer
**********************************************************************/
void Console::display_tournament_scores(int a_computer_score, int a_human_score)
{
    cout << endl << "***TOURNAMENT SCORES***" << endl;
    cout << "Computer: " << a_computer_score << endl;
    cout << "Human: " << a_human_score << endl;
}

/**********************************************************************
Function Name: display_tournament_result
Purpose: To display tournament result
Parameters:
    a_computer_score, an integer
    a_human_score, an integer
**********************************************************************/
void Console::display_tournament_result(int a_computer_score, int a_human_score)
{
    cout << endl << "***FINAL RESULT***" << endl;
    if (a_computer_score > a_human_score)
    {
        cout << "COMPUTER WINS!";
    }
    else if (a_computer_score < a_human_score)
    {
        cout << "HUMAN WINS!";
    }
    else
    {
        cout << "IT'S A TIE!";
    }
    cout << endl << endl;
}

/**********************************************************************
Function Name: string_to_vector
Purpose: To tokenize a string
Parameters:
    a_string, a string
Return Value: String tokens, a vector of strings
**********************************************************************/
vector<string> Console::string_to_vector(string a_string)
{
    vector<string> tokens;

    string token;

    for_each(begin(a_string), end(a_string), [&](char const c)
    {
        if (c != ' ')
        {
            token += c;
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
