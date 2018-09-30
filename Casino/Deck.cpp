#include "pch.h"
#include "Deck.h"
#include <vector>
#include <ctime>

Deck::Deck()
{
    // create deck
    vector<Card> cards;
    for (string suit : { "C", "D", "H", "S" })
    {
        for (string value : { "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K", "A" })
        {
            cards.push_back(Card(suit + value));
        }
    }

    // shuffle deck
    srand((unsigned int)time(NULL));
    for (int size = 52; size > 0; size--)
    {
        int index = rand() % size;
        m_cards.push_back(cards[index]);
        cards.erase(cards.begin() + index);
    }
}

Card Deck::Draw()
{
    Card card = m_cards.back();
    m_cards.pop_back();
    return card;
}

string Deck::ToString()
{
    string info;

    for (Card card : m_cards)
    {
        info += " " + card.get_name();
    }

    return info;
}
