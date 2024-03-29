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
    void add_loose_card(Card a_card);
    void remove_loose_card(Card a_card);
    void remove_loose_set(Set a_set);
    void add_build(Build a_build);
    void remove_build(Build a_build);
    void increase_build(int a_index, Card a_card, bool a_is_human);
    void extend_build(int a_index, Set a_set, bool a_is_human);
    bool contains(Build a_build);
    bool contains(Card a_card);
    string ToString();
private:
    Set m_loose_set;
    vector<Build> m_builds;
};
