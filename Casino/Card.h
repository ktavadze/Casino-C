#pragma once

using namespace std;

class Card
{
public:
    Card() {}
    Card(string a_name);
    inline string get_name()
    {
        return m_name;
    }
    inline int get_value()
    {
        return m_value;
    }
    inline int set_value(int a_value)
    {
        m_value = a_value;
    }
    inline bool operator==(const Card a_card) const
    {
        return m_name == a_card.m_name;
    }
    bool is_spade();
    bool is_ace();
private:
    string m_name;
    int m_value;
};
