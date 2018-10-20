#pragma once

using namespace std;

class Build
{
public:
    Build() {}
    Build(bool a_is_human, Set a_set)
    {
        m_is_human = a_is_human;

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
    inline vector<Set> get_sets()
    {
        return m_sets;
    }
    int get_value();
    int get_weight();
    void increase(Card a_card);
    void extend(Set a_set);
    bool equals(Build a_build);
    bool contains(Set a_set);
    bool contains(Card a_card);
    string ToString();
private:
    bool m_is_human;
    int m_value;
    int m_weight;
    vector<Set> m_sets;
};
