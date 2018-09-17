#include "pch.h"
#include "Tournament.h"

using namespace std;

int main()
{
    cout << "Welcome to Casino!" << endl;

    int choice;
    do
    {
        cout << endl << "Main menu" << endl;
        cout << "1. Start a new game" << endl;
        cout << "2. Load an old game" << endl;
        cout << "3. Quit the game" << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (choice != 1 && choice != 2 && choice != 3);

    Tournament tournament;
    switch (choice)
    {
    case 1:
        tournament.Start();
        break;
    case 2:
        tournament.Load();
        break;
    case 3:
        return 0;
    }

    return 0;
}
