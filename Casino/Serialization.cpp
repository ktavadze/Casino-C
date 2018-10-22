#include "pch.h"
#include "Serialization.h"

void Serialization::save_game(string m_state)
{
    ofstream outStream("../Data/data.txt");

    if (outStream)
    {
        outStream << m_state;
        outStream.close();
        exit(0);
    }
    else
    {
        Console::display_message("ERROR: cannot save game!");
    }
}
