#pragma once

#include "Card.h"
#include <stack>

class Deck
{
public:
    Deck();
    Card Draw();
private:
    std::stack<Card> m_cards;
};
