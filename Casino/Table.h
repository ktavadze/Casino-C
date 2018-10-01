#pragma once

using namespace std;

class Table
{
public:
    Table() {}
    inline Set get_cards()
    {
        return m_cards;
    }
    inline void set_cards(Set a_cards)
    {
        m_cards = a_cards;
    }
    inline vector<Build> get_builds()
    {
        return m_builds;
    }
    inline void set_builds(vector<Build> a_builds)
    {
        m_builds = a_builds;
    }
    void AddCard(Card a_card);
    void RemoveCard(Card a_card);
    void AddBuild(Build a_build);
    bool Contains(Card a_card);
    string ToString();
private:
    Set m_cards;
    vector<Build> m_builds;
};
