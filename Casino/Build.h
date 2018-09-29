#pragma once

using namespace std;

class Build
{
public:
    Build() {}
    Build(vector<Card> a_cards, bool a_is_human)
    {
        m_value = 0;
        for (Card card : a_cards)
        {
            m_value += card.get_value();
        }

        m_cards.push_back(a_cards);

        m_is_human = a_is_human;
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
    inline bool is_human()
    {
        return m_is_human;
    }
    inline void is_human(bool a_is_human)
    {
        m_is_human = a_is_human;
    }
    bool AddCard(Card a_card);
    bool AddBuild(vector<Card> a_cards);
    string ToString();
private:
    int m_value;
    vector<vector<Card>> m_cards;
    bool m_is_human;
};
