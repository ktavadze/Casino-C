#pragma once

#include "Card.h"
#include "Build.h"
#include <vector>

class Table
{
public:
    Table() {}
    inline std::vector<Card> get_cards()
    {
        return m_cards;
    }
    inline void set_cards(std::vector<Card> a_cards)
    {
        m_cards = a_cards;
    }
    inline std::vector<Build> get_builds()
    {
        return m_builds;
    }
    inline void set_builds(std::vector<Build> a_builds)
    {
        m_builds = a_builds;
    }
    void AddCard(Card a_card);
private:
    std::vector<Card> m_cards;
    std::vector<Build> m_builds;
};
