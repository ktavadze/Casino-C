#include "pch.h"
#include "Card.h"

Card::Card(string a_name)
{
    m_name = a_name;

    // Assign value
    switch (a_name[1])
    {
    case '2':
        m_value = 2;
        break;
    case '3':
        m_value = 3;
        break;
    case '4':
        m_value = 4;
        break;
    case '5':
        m_value = 5;
        break;
    case '6':
        m_value = 6;
        break;
    case '7':
        m_value = 7;
        break;
    case '8':
        m_value = 8;
        break;
    case '9':
        m_value = 9;
        break;
    case 'X':
        m_value = 10;
        break;
    case 'J':
        m_value = 11;
        break;
    case 'Q':
        m_value = 12;
        break;
    case 'K':
        m_value = 13;
        break;
    case 'A':
        m_value = 1;
        break;
    }

    // Assign weight
    m_weight = 1;

    if (a_name == "DX")
    {
        m_weight += 4;
    }
    else if (a_name == "S2" || a_name == "SA")
    {
        m_weight += 3;
    }
    else if (a_name[1] == 'A')
    {
        m_weight += 2;
    }
    else if (a_name[0] == 'S')
    {
        m_weight += 1;
    }
}

bool Card::is_spade()
{
    if (m_name[0] == 'S')
    {
        return true;
    }

    return false;
}

bool Card::is_ace()
{
    if (m_name[1] == 'A')
    {
        return true;
    }

    return false;
}
