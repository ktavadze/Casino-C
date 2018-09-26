#include "pch.h"
#include "Table.h"

using namespace std;

void Table::AddCard(Card a_card)
{
    m_cards.push_back(a_card);
}

std::string Table::ToString()
{
    string info;

    for (Card card : m_cards)
    {
        info += " " + card.get_name();
    }

    return info;
}
