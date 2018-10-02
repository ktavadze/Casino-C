#pragma once

using namespace std;

class Table
{
public:
    Table() {}
    inline Set get_loose_set()
    {
        return m_loose_set;
    }
    inline void set_loose_set(Set a_set)
    {
        m_loose_set = a_set;
    }
    inline vector<Build> get_builds()
    {
        return m_builds;
    }
    inline void set_builds(vector<Build> a_builds)
    {
        m_builds = a_builds;
    }
    void add_card(Card a_card);
    void remove_card(Card a_card);
    void add_build(Build a_build);
    void remove_build(Build a_build);
    int index_of(Build a_build);
    bool contains(Build a_build);
    bool contains(Card a_card);
    string ToString();
private:
    Set m_loose_set;
    vector<Build> m_builds;
};
