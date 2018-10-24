#include "pch.h"
#include "Deck.h"
#include <ctime>

Deck::Deck()
{
    vector<Card> cards;
    for (string suit : { "C", "D", "H", "S" })
    {
        for (string value : { "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K", "A" })
        {
            cards.push_back(Card(suit + value));
        }
    }

    srand((unsigned int)time(NULL));
    for (int size = 52; size > 0; size--)
    {
        int index = rand() % size;
        m_cards.push_back(cards[index]);
        cards.erase(cards.begin() + index);
    }
}

Set Deck::draw_set()
{
    Set set;

    for (int i = 0; i < 4; i++)
    {
        if (!is_empty())
        {
            set.add_card(m_cards.front());
            m_cards.erase(m_cards.begin());
        }
    }

    return set;
}

bool Deck::is_empty()
{
    if (m_cards.size() == 0)
    {
        return true;
    }

    return false;
}

string Deck::ToString()
{
    string info;

    int count = 0;
    for (Card card : m_cards)
    {
        count++;
        if (count > 1)
        {
            info += " ";
        }
        info += card.get_name();
    }

    return info;
}
