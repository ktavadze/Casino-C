#pragma once

class Card
{
public:
    Card() {}
    Card(std::string a_name);
    inline std::string get_name()
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
private:
    std::string m_name;
    int m_value;
};
