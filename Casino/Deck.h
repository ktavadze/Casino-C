#pragma once

#include "Card.h"
#include <stack>

class Deck
{
public:
    Deck();
    inline void set_cards(std::stack<Card> a_cards)
    {
        m_cards = a_cards;
    }
    Card Draw();
private:
    std::stack<Card> m_cards;
};
