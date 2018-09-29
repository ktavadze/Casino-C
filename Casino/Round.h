#pragma once

#include "Computer.h"
#include "Human.h"
#include "Table.h"
#include "Deck.h"

using namespace std;

class Round
{
public:
    Round() {}
    Round(int a_number, Computer *a_computer, Human *a_human, bool a_human_next)
    {
        m_number = a_number;
        m_computer = a_computer;
        m_human = a_human;
        m_human_next = a_human_next;
    }
    void Start();
    void DealCards();
    string ToString();
private:
    int m_number;
    Computer *m_computer;
    Human *m_human;
    bool m_human_next;
    Table m_table;
    Deck m_deck;
};
