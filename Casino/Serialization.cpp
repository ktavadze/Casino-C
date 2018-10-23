#include "pch.h"
#include "Serialization.h"
#include <algorithm>
#include <stack>

void Serialization::save_game(string m_state)
{
    ofstream outfile("../Data/data.txt");

    if (outfile)
    {
        outfile << m_state;
        outfile.close();
        exit(0);
    }
    else
    {
        Console::display_message("ERROR: cannot save game!");
    }
}

Tournament Serialization::load_game()
{
    ifstream infile("../Data/data.txt");

    if (infile.is_open()) {
        int round_number = 0;
        int player_number = 0;
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

        string line;

        while (getline(infile, line)) {
            if (line.find("Round") != string::npos) {
                int index = line.find(": ");
                round_number = stoi(line.substr(index + 2));
            }

            if (line.find("Score") != string::npos) {
                int index = line.find(": ");
                if (player_number == 0) {
                    computer_score = stoi(line.substr(index + 2));
                }
                else {
                    human_score = stoi(line.substr(index + 2));
                }
            }

            if (line.find("Hand") != string::npos) {
                int index = line.find(": ");
                if (player_number == 0) {
                    string computer_hand_string = line.substr(index + 2);

                    vector<string> computer_hand_tokens = tokenize_set(computer_hand_string);

                    computer_hand = generate_set(computer_hand_tokens);

                }
                else {
                    string human_hand_string = line.substr(index + 2);

                    vector<string> human_hand_tokens = tokenize_set(human_hand_string);

                    human_hand = generate_set(human_hand_tokens);
                }
            }

            if (line.find("Pile") != string::npos) {
                int index = line.find(": ");
                if (player_number == 0) {
                    string computer_pile_string = line.substr(index + 2);

                    vector<string> computer_pile_tokens = tokenize_set(computer_pile_string);

                    computer_pile = generate_set(computer_pile_tokens);

                    player_number++;
                }
                else {
                    string human_pile_string = line.substr(index + 2);

                    vector<string> human_pile_tokens = tokenize_set(human_pile_string);

                    human_pile = generate_set(human_pile_tokens);
                }
            }

            if (line.find("Table") != string::npos) {
                int startBuildIndex = line.find(":");
                int endBuildIndex = line.find_last_of(']');
                int startLooseCardIndex = endBuildIndex + 2;

                string buildString = line.substr(startBuildIndex + 3, endBuildIndex - startBuildIndex - 2);

                vector<string> serializedBuilds = tokenize_builds(buildString);

                for (string buildStr : serializedBuilds) {
                    builds.push_back(generate_build(buildStr));
                }

                string looseCardStrings = line.substr(startLooseCardIndex);

                vector<string> cardSerialData = tokenize_set(looseCardStrings);

                loose_set = generate_set(cardSerialData);
            }

            if (line.find("Deck") != string::npos) {
                int index = line.find(": ");
                string deck_string = line.substr(index + 2);

                vector<string> deck_tokens = tokenize_set(deck_string);

                for (string token : deck_tokens)
                {
                    deck_cards.push_back(Card(token));
                }
            }

            if (line.find("Next Player") != string::npos) {
                int index = line.find(": ");
                string next_player = line.substr(index + 2);

                if (next_player == "Computer")
                {
                    human_is_next = false;
                }
            }

            if (line.find("Build Owner") != string::npos) {
                vector<string> owners;

                int promptIndex = line.find(":");
                line.erase(line.begin(), line.begin() + promptIndex + 1);

                while (line != "") {
                    if (line.find(" [ ") != string::npos && line.find(" ] ") != string::npos) {
                        int startOfBuildIndex = line.find(" [ ");
                        int endOfBuildIndex = line.find(" ] ");
                        line.erase(line.begin() + startOfBuildIndex, line.begin() + endOfBuildIndex + 3);
                        if (line.find(" [ ") != string::npos) {
                            int nextBuild = line.find(" [ ");
                            string name = line.substr(0, nextBuild);
                            name.erase(remove(name.begin(), name.end(), ' '), name.end());
                            owners.push_back(name);
                            line.erase(line.begin(), line.begin() + nextBuild);
                        }
                        else {
                            line.erase(remove(line.begin(), line.end(), ' '), line.end());
                            owners.push_back(line);
                            line.erase();
                        }
                    }
                    else {
                        break;
                    }
                }

                for (unsigned int i = 0; i < owners.size(); i++) {
                    if (owners[i] == "Human") {
                        builds.at(i).is_human(true);
                    }
                    else {
                        builds.at(i).is_human(false);
                    }
                }
            }
        }

        cout << "\nRound number: " << round_number << endl;
        cout << "Computer score: " << computer_score << endl;
        cout << "Computer hand: " << computer_hand.ToString() << endl;
        cout << "Computer pile: " << computer_pile.ToString() << endl;
        cout << "Human score: " << human_score << endl;
        cout << "Human hand: " << human_hand.ToString() << endl;
        cout << "Human pile: " << human_pile.ToString() << endl;
        cout << "Loose set: " << loose_set.ToString() << endl;
        cout << "Builds: ";
        for (Build build : builds) {
            cout << build.ToString();
        }
        cout << "\nDeck:";
        for (Card card : deck_cards) {
            cout << " " << card.get_name();
        }
        cout << "\nHuman next: " << human_is_next << endl << endl;

        Computer computer(human_is_next, computer_score, computer_hand, computer_pile);
        Human human(!human_is_next, human_score, human_hand, human_pile);

        Table table(loose_set, builds);
        Deck deck(deck_cards);
        Round round(round_number, &computer, &human);

        cout << round.ToString();

        infile.close();

        return Tournament(computer, human, round);
    }
    else {
        Console::display_message("ERROR: cannot load game!");

        return Tournament();
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
