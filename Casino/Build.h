#pragma once

using namespace std;

class Build
{
public:
    Build() {}
    Build(vector<Card> a_cards)
    {
        m_value = 0;
        for (Card card : a_cards)
        {
            m_value += card.get_value();
        }

        m_cards.push_back(a_cards);
    }
    inline int get_value()
    {
        return m_value;
    }
    inline void set_cards(vector<vector<Card>> a_cards)
    {
        m_cards = a_cards;
    }
    inline vector<vector<Card>> get_cards()
    {
        return m_cards;
    }
    bool AddCard(Card a_card);
    bool AddBuild(vector<Card> a_cards);
private:
    int m_value;
    vector<vector<Card>> m_cards;
};
