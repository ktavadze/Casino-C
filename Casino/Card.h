#pragma once

class Card
{
public:
    Card() {}
    Card(char a_suit, int a_value);
    inline char get_suit()
    {
        return m_suit;
    }
    inline int get_value()
    {
        return m_value;
    }
private:
    char m_suit;
    int m_value;
};
