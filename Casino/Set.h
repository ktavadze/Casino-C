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
    inline int get_value()
    {
        return m_value;
    }
    inline vector<Card> get_cards()
    {
        return m_cards;
    }
    void AddCard(Card a_card);
    bool Contains(Card a_card);
    string ToString();
private:
    int m_value;
    vector<Card> m_cards;
};
