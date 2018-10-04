#pragma once

using namespace std;

class Deck
{
public:
    Deck();
    Deck(vector<Card> a_cards)
    {
        m_cards = a_cards;
    }
    Set draw_set();
    bool is_empty();
    string ToString();
private:
    vector<Card> m_cards;
};
