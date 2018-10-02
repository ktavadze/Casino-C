#pragma once

using namespace std;

class Build
{
public:
    Build() {}
    Build(bool a_is_human, Set a_set)
    {
        m_is_human = a_is_human;

        m_value = a_set.get_value();

        m_sets.push_back(a_set);
    }
    inline bool is_human()
    {
        return m_is_human;
    }
    inline void is_human(bool a_is_human)
    {
        m_is_human = a_is_human;
    }
    inline int get_value()
    {
        return m_value;
    }
    inline vector<Set> get_sets()
    {
        return m_sets;
    }
    bool Increase(Card a_card);
    bool Extend(Set a_set);
    bool contains(Card a_card);
    string ToString();
private:
    bool m_is_human;
    int m_value;
    vector<Set> m_sets;
};
