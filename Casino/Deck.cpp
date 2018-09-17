#include "pch.h"
#include "Deck.h"
#include <vector>
#include <ctime>

using namespace std;

Deck::Deck()
{
    // create deck
    vector<Card> cards;
    for (char suit : { 'C', 'D', 'H', 'S' })
    {
        for (int value = 1; value < 14; value++)
        {
            cards.push_back(Card(suit, value));
        }
    }

    // shuffle deck
    srand(time(NULL));
    for (int size = 52; size > 0; size--)
    {
        int index = rand() % size;
        m_cards.push(cards[index]);
        cards.erase(cards.begin() + index);
    }
}

Card Deck::Draw()
{
    Card card = m_cards.top();
    m_cards.pop();
    return card;
}
