#pragma once

using namespace std;

class Deck
{
public:
    Deck();
    inline Set get_cards()
    {
        return m_cards;
    }
    inline void set_cards(vector<Card> a_cards)
    {
        m_cards = a_cards;
    }
    Card draw();
    string ToString();
private:
    vector<Card> m_cards;
};
