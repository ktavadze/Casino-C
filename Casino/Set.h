#pragma once

using namespace std;

class Set
{
public:
    Set() {}
    Set(vector<Card> a_cards)
    {
        m_cards = a_cards;
    }
    inline void reset()
    {
        m_cards.clear();
    }
    inline int get_size()
    {
        return m_cards.size();
    }
    inline vector<Card> get_cards()
    {
        return m_cards;
    }
    inline Card get_card(int a_index)
    {
        return m_cards.at(a_index);
    }
    inline Card get_first_card()
    {
        return m_cards.front();
    }
    inline Card get_last_card()
    {
        return m_cards.back();
    }
    int get_value();
    int get_weight();
    void add_card(Card a_card);
    void remove_card(Card a_card);
    void add_set(Set a_set);
    void remove_set(Set a_set);
    bool equals(Set a_set);
    bool contains(vector<Set> a_sets);
    bool contains(Set a_set);
    bool contains(Card a_card);
    string ToString();
private:
    vector<Card> m_cards;
};
