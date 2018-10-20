#pragma once

using namespace std;

class Card
{
public:
    Card()
    {
        m_name = "UN";
        m_value = 0;
        m_weight = 0;
    }
    Card(string a_name);
    inline string get_name()
    {
        return m_name;
    }
    inline int get_value()
    {
        return m_value;
    }
    inline int get_weight()
    {
        return m_weight;
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
    int m_weight;
};
