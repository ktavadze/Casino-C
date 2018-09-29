#pragma once

using namespace std;

class Deck
{
public:
    Deck();
    inline vector<Card> get_cards()
    {
        return m_cards;
    }
    inline void set_cards(vector<Card> a_cards)
    {
        m_cards = a_cards;
    }
    Card Draw();
    string ToString();
private:
    vector<Card> m_cards;
};
