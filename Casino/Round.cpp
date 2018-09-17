#include "pch.h"
#include "Round.h"

using namespace std;

void Round::Start()
{
    for (int i = 52; i > 0; i--)
    {
        Card card = m_deck.Draw();
        cout << i << "\t" << card.get_suit() << card.get_value() << endl;
    }
}
