#pragma once

using namespace std;

class Player
{
public:
    Player() {}
    inline bool is_human()
    {
        return m_is_human;
    }
    inline bool is_next()
    {
        return m_is_next;
    }
    inline void is_next(bool a_is_next)
    {
        m_is_next = a_is_next;
    }
    inline bool captured_last()
    {
        return m_captured_last;
    }
    inline void captured_last(bool a_captured_last)
    {
        m_captured_last = a_captured_last;
    }
    inline int get_score()
    {
        return m_score;
    }
    inline void set_score(int a_score)
    {
        m_score = a_score;
    }
    inline Set get_hand()
    {
        return m_hand;
    }
    inline void set_hand(Set a_hand)
    {
        m_hand = a_hand;
    }
    inline Set get_pile()
    {
        return m_pile;
    }
    inline void set_pile(Set a_pile)
    {
        m_pile = a_pile;
    }
    inline void add_to_pile(Card a_card)
    {
        m_pile.add_card(a_card);
    }
    inline void clear_pile()
    {
        m_pile.reset();
    }
    virtual int make_move(Table & a_table)
    {
        return 0;
    }
    void ask_for_help(Table a_table);
    string ToString();
protected:
    bool m_is_human;
    bool m_is_next;
    bool m_captured_last;
    int m_score;
    Set m_hand;
    Set m_pile;

    void capture_loose_card(Table & a_table, Card a_card);
    void capture_build(Table & a_table, Build a_build);
    bool can_increase(Table a_table);
    bool can_extend(Table a_table);
    bool can_create(Table a_table);
    bool can_capture(Table a_table);
    bool reserved_for_capture(Table a_table, Card a_card);
    bool owns_build(Table a_table);
    int count_cards_held(int a_value);

    Build find_best_increase(Table a_table);
    Build find_best_extend(Table a_table);
    Build find_best_create(Table a_table);
    Set find_best_capture(Table a_table);
    Card find_best_trail(Table a_table);

    vector<Set> generate_set_combinations(Set a_set);
    bool vector_contains_set(vector<Set> a_vector, Set a_set);
};
