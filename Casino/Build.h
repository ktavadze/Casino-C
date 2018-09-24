#pragma once

#include "Card.h"
#include <vector>

class Build
{
public:
    Build() {}
    Build(std::vector<Card> a_cards)
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
    inline void set_cards(std::vector<std::vector<Card>> a_cards)
    {
        m_cards = a_cards;
    }
    inline std::vector<std::vector<Card>> get_cards()
    {
        return m_cards;
    }
    bool AddCard(Card a_card);
    bool AddBuild(std::vector<Card> a_cards);
private:
    int m_value;
    std::vector<std::vector<Card>> m_cards;
};
