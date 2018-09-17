#pragma once

class Card
{
public:
    Card() {}
    Card(char a_suit, int a_value);
    inline char suit()
    {
        return m_suit;
    }
    inline int value()
    {
        return m_value;
    }
private:
    char m_suit;
    int m_value;
};
