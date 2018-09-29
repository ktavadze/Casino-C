#include "pch.h"
#include "Table.h"

void Table::AddCard(Card a_card)
{
    m_cards.push_back(a_card);
}

string Table::ToString()
{
    string info;

    for (Card card : m_cards)
    {
        info += " " + card.get_name();
    }

    return info;
}
