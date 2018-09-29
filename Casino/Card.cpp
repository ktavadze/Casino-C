#include "pch.h"
#include "Card.h"

Card::Card(string a_name)
{
    m_name = a_name;
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
        m_value = 14;
        break;
    }
}
