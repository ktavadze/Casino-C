#pragma once

using namespace std;

class Table
{
public:
    Table() {}
    Table(Set a_loose_set, vector<Build> a_builds)
    {
        m_loose_set = a_loose_set;
        m_builds = a_builds;
    }
    inline Set get_loose_set()
    {
        return m_loose_set;
    }
    inline void set_loose_set(Set a_loose_set)
    {
        m_loose_set = a_loose_set;
    }
    inline vector<Build> get_builds()
    {
        return m_builds;
    }
    void add_card(Card a_card);
    void remove_card(Card a_card);
    void add_build(Build a_build);
    void remove_build(Build a_build);
    bool contains(Build a_build);
    bool contains(Card a_card);
    string ToString();
private:
    Set m_loose_set;
    vector<Build> m_builds;
};
