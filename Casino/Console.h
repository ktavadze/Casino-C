#pragma once

#include "Card.h"
#include "Set.h"
#include "Build.h"
#include "Table.h"

using namespace std;

class Console
{
public:
    static int process_main_menu();
    static bool process_coin_toss();
    static int process_turn_menu(bool a_is_human);
    static int process_move_menu();
    static int process_build_menu();
    static int pick_player_card(Set a_hand);
    static int pick_build(vector<Build> a_builds);
    static Set pick_loose_set(Set a_set);
    static Set pick_table_set(Table a_table);
    static void display_message(string a_message);
private:
    static vector<string> string_to_vector(string a_string, char a_delimiter);
};
