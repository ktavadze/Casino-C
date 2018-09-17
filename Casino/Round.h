#pragma once

#include "Computer.h"
#include "Human.h"
#include "Deck.h"

class Round
{
public:
    Round() {}
    void Start(Computer& a_computer, Human& a_human, bool a_human_first);
private:
    Deck m_deck;
    std::vector<Card> m_table;
};
