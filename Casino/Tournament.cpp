#include "pch.h"
#include "Tournament.h"
#include <ctime>
#include <string>

using namespace std;

void Tournament::Start()
{
    int choice;
    do
    {
        cout << endl << "Coin toss" << endl;
        cout << "1. Guess heads" << endl;
        cout << "2. Guess tails" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice != 1 && choice != 2);

    srand(time(NULL));
    int coin = rand() % 2 + 1;

    string result;
    if (coin == 1)
    {
        result = "Heads";
    }
    else
    {
        result = "Tails";
    }
    cout << endl << "Result" << endl;
    cout << coin << " - " << result << endl;

    if (choice == coin)
    {
        m_round.Start(m_computer, m_human, true);
    }
    else
    {
        m_round.Start(m_computer, m_human, false);
    }
}
