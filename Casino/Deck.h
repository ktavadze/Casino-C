#pragma once

#include "Card.h"
#include <vector>

class Deck
{
public:
    Deck();
    inline std::vector<Card> get_cards()
    {
        return m_cards;
    }
    inline void set_cards(std::vector<Card> a_cards)
    {
        m_cards = a_cards;
    }
    Card Draw();
    std::string ToString();
private:
    std::vector<Card> m_cards;
};
