#pragma once

using namespace std;

class Set
{
public:
    Set() {}
    Set(vector<Card> a_cards)
    {
        m_value = 0;
        for (Card card : a_cards)
        {
            m_value += card.get_value();
        }

        m_cards = a_cards;
    }
    inline void reset()
    {
        m_value = 0;

        m_cards.clear();
    }
    inline int get_value()
    {
        return m_value;
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
    void add_card(Card a_card);
    void remove_card(Card a_card);
    bool equals(Set a_set);
    bool contains(Card a_card);
    string ToString();
private:
    int m_value;
    vector<Card> m_cards;
};
