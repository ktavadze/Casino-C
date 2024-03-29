#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include "Computer.h"
#include "Human.h"
#include "Round.h"
#include "Tournament.h"

using namespace std;

class Serialization
{
public:
    static bool save_game(string a_name, string a_state);
    static bool load_game(string a_name, Tournament & a_tournament);
    static void seed_deck(Deck & a_deck);
private:
    static vector<string> tokenize_set(string a_string);
    static vector<string> tokenize_builds(string a_string);
    static Set generate_set(vector<string> a_tokens);
    static Build generate_build(string a_string);
};
