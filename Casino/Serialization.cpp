#include "pch.h"
#include "Serialization.h"
#include <algorithm>
#include <stack>

bool Serialization::save_game(string a_name, string a_state)
{
    ofstream outfile("../Data/" + a_name);

    if (outfile)
    {
        outfile << a_state;
        outfile.close();
        
        return true;
    }
    else
    {
        Console::display_message("ERROR: cannot save game!");

        return false;
    }
}

bool Serialization::load_game(string a_name, Tournament & a_tournament)
{
    ifstream infile("../Data/" + a_name);

    if (infile.is_open())
    {
        int round_number = 0;
        int computer_score = 0;
        Set computer_hand;
        Set computer_pile;
        int human_score = 0;
        Set human_hand;
        Set human_pile;
        Set loose_set;
        vector<Build> builds;
        vector<Card> deck_cards;
        bool human_is_next = true;

        bool read_computer = true;

        string line;

        while (getline(infile, line))
        {
            if (line.find("Round") != string::npos)
            {
                int index = line.find(":");

                round_number = stoi(line.substr(index + 2));
            }
            else if (line.find("Score") != string::npos)
            {
                int index = line.find(":");

                if (read_computer)
                {
                    computer_score = stoi(line.substr(index + 2));
                }
                else
                {
                    human_score = stoi(line.substr(index + 2));
                }
            }
            else if (line.find("Hand") != string::npos)
            {
                if (line.length() > 9)
                {
                    int index = line.find(":");

                    if (read_computer)
                    {
                        string computer_hand_string = line.substr(index + 2);

                        vector<string> computer_hand_tokens = tokenize_set(computer_hand_string);

                        computer_hand = generate_set(computer_hand_tokens);
                    }
                    else
                    {
                        string human_hand_string = line.substr(index + 2);

                        vector<string> human_hand_tokens = tokenize_set(human_hand_string);

                        human_hand = generate_set(human_hand_tokens);
                    }
                }
            }
            else if (line.find("Pile") != string::npos)
            {
                int index = line.find(":");

                if (read_computer)
                {
                    if (line.length() > 9)
                    {
                        string computer_pile_string = line.substr(index + 2);

                        vector<string> computer_pile_tokens = tokenize_set(computer_pile_string);

                        computer_pile = generate_set(computer_pile_tokens);
                    }

                    read_computer = false;
                }
                else
                {
                    if (line.length() > 9)
                    {
                        string human_pile_string = line.substr(index + 2);

                        vector<string> human_pile_tokens = tokenize_set(human_pile_string);

                        human_pile = generate_set(human_pile_tokens);
                    }
                }
            }
            else if (line.find("Table") != string::npos)
            {
                int loose_set_start_index = 7;

                if (line.find("[") != string::npos)
                {
                    int builds_start_index = line.find(":");
                    int builds_end_index = line.find_last_of("]");

                    loose_set_start_index = builds_end_index + 2;

                    string builds_string = line.substr(builds_start_index + 3,
                        builds_end_index - builds_start_index - 2);

                    vector<string> builds_tokens = tokenize_builds(builds_string);

                    for (string token : builds_tokens)
                    {
                        builds.push_back(generate_build(token));
                    }
                }

                string loose_set_string = line.substr(loose_set_start_index);

                vector<string> loose_set_tokens = tokenize_set(loose_set_string);

                loose_set = generate_set(loose_set_tokens);
            }
            else if (line.find("Build Owner") != string::npos)
            {
                vector<string> build_owners;

                int index = line.find(":");

                line.erase(line.begin(), line.begin() + index + 1);

                while (line != "")
                {
                    if (line.find(" [ ") != string::npos && line.find(" ] ") != string::npos)
                    {
                        int build_start_index = line.find(" [ ");
                        int build_end_index = line.find(" ] ");

                        line.erase(line.begin() + build_start_index, line.begin() + build_end_index + 3);

                        if (line.find(" [ ") != string::npos)
                        {
                            int next_build_index = line.find(" [ ");

                            string owner = line.substr(0, next_build_index);

                            owner.erase(remove(owner.begin(), owner.end(), ' '), owner.end());

                            build_owners.push_back(owner);

                            line.erase(line.begin(), line.begin() + next_build_index);
                        }
                        else
                        {
                            line.erase(remove(line.begin(), line.end(), ' '), line.end());

                            build_owners.push_back(line);

                            line.erase();
                        }
                    }
                    else
                    {
                        break;
                    }
                }

                for (unsigned int i = 0; i < build_owners.size(); i++)
                {
                    if (build_owners[i] == "Computer")
                    {
                        builds.at(i).is_human(false);
                    }
                    else
                    {
                        builds.at(i).is_human(true);
                    }
                }
            }
            else if (line.find("Deck") != string::npos)
            {
                if (line.length() > 6)
                {
                    int index = line.find(":");

                    string deck_string = line.substr(index + 2);

                    vector<string> deck_tokens = tokenize_set(deck_string);

                    for (string token : deck_tokens)
                    {
                        deck_cards.push_back(Card(token));
                    }
                }
            }
            else if (line.find("Next Player") != string::npos)
            {
                int index = line.find(":");

                string next_player = line.substr(index + 2);

                if (next_player == "Computer")
                {
                    human_is_next = false;
                }
            }
        }

        Computer computer(!human_is_next, computer_score, computer_hand, computer_pile);
        Human human(human_is_next, human_score, human_hand, human_pile);

        Table table(loose_set, builds);
        Deck deck(deck_cards);

        Round round(round_number, table, deck);

        a_tournament = Tournament(computer, human, round);

        infile.close();

        return true;
    }
    else
    {
        Console::display_message("ERROR: cannot load game!");

        return false;
    }
}

void Serialization::seed_deck(Deck & a_deck)
{
    ifstream infile("../Data/deck.txt");

    if (infile.is_open())
    {
        vector<Card> cards;

        string name;
        string line;

        while (getline(infile, line))
        {
            cards.push_back(Card(line));
        }

        a_deck = Deck(cards);
    }
    else
    {
        Console::display_message("ERROR: cannot seed deck!");
    }
}

vector<string> Serialization::tokenize_set(string a_string)
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

vector<string> Serialization::tokenize_builds(string a_string)
{
    vector<string> tokens;

    while (a_string != "") {
        int endOfBuildIndex = a_string.find(" ] [ ");

        if (endOfBuildIndex == -1)
            endOfBuildIndex = a_string.find_last_of("]");

        string build = a_string.substr(0, endOfBuildIndex + 2);
        tokens.push_back(build);

        if (a_string.find(" ] [ ") != string::npos)
            a_string.erase(a_string.begin(), a_string.begin() + (endOfBuildIndex + 2));
        else
            a_string.clear();
    }

    for (unsigned int i = 0; i < tokens.size(); i++) {
        if (tokens[i][0] == ' ') {
            tokens[i].erase(tokens[i].begin(), tokens[i].begin() + 1);
        }
    }

    return tokens;
}

Set Serialization::generate_set(vector<string> a_tokens)
{
    Set set;

    for (string token : a_tokens)
    {
        set.add_card(Card(token));
    }

    return set;
}

Build Serialization::generate_build(string a_string)
{
    Build build;
    vector<Set> sets;
    stack<unsigned> brackets;

    for (unsigned int i = 0; i < a_string.length() - 1; i++) {
        if (a_string[i] == '[') {
            brackets.push(i);
        }
        else if (a_string[i] == ']') {
            unsigned int top_index = brackets.top();
            string buildSubString = a_string.substr(top_index + 1, i - top_index - 1);
            vector<string> build_str = tokenize_set(buildSubString);
            Set buildSet = generate_set(build_str);

            unsigned sum = 0;
            for (int j = 0; j < buildSet.get_size(); j++) {
                sum += buildSet.get_card(j).get_value();
            }

            sets.push_back(buildSet);

            brackets.pop();
        }
    }

    for (unsigned int i = 0; i < sets.size(); i++) {
        build.extend(sets.at(i));
    }

    return build;
}
