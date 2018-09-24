#include "pch.h"
#include "Player.h"

using namespace std;

void Player::Play(Table& a_table)
{
    while (true)
    {
        int choice;
        cout << "1. Save the game" << endl;
        cout << "2. Make a move" << endl;
        cout << "3. Quit the game" << endl;
        cin >> choice;

        if (choice == 2)
        {
            if (MakeMove(a_table))
            {
                break;
            }
        }
        else if (choice == 3)
        {
            exit(0);
        }
    }
}

bool Player::MakeMove(Table& a_table)
{
    int choice;
    cout << endl << "Make move" << endl;
    cout << "1. Build" << endl;
    cout << "2. Capture" << endl;
    cout << "3. Trail" << endl;
    cin >> choice;

    if (choice == 3)
    {
        int index;
        cout << endl << "Which card would you like to trail? ";
        cin >> index;

        if (Trail(a_table, index))
        {
            return true;
        }
    }

    return false;
}

bool Player::Trail(Table& a_table, int a_index)
{
    if (a_index >= m_hand.size())
    {
        return false;
    }

    Card card = m_hand[a_index];
    a_table.AddCard(card);
    m_hand.erase(m_hand.begin() + a_index);

    return true;
}
