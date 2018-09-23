#pragma once

#include "Computer.h"
#include "Human.h"
#include "Deck.h"

class Round
{
public:
    Round() {}
    void Start(Computer& a_computer, Human& a_human, bool a_human_first);
    void DealCards();
    void DisplayCards();
private:
    bool m_human_next;
    Computer *m_computer;
    Human *m_human;
    Deck m_deck;
    std::vector<Card> m_table;
};
