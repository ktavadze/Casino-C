#include "pch.h"
#include "Player.h"

void Player::Play(Table & a_table)
{
    while (true)
    {
        int choice = Console::ProcessTurnMenu(m_is_human);

        if (m_is_human)
        {
            switch (choice)
            {
            case 1:
                // TODO: save game
                exit(0);
            case 2:
                if (MakeMove(a_table))
                {
                    return;
                }
                break;
            case 3:
                // TODO: ask for help
                exit(0);
            case 4:
                exit(0);
            }
        }
        else
        {
            switch (choice)
            {
            case 1:
                // TODO: save game
                exit(0);
            case 2:
                if (MakeMove(a_table))
                {
                    return;
                }
                break;
            case 3:
                exit(0);
            }
        }
    }
}

bool Player::MakeMove(Table & a_table)
{
    int choice = Console::ProcessMoveMenu();

    switch (choice)
    {
    case 1:
        // TODO: build
        if (BuildMove(a_table))
        {
            return true;
        }
    case 2:
        // TODO: capture
        return false;
    case 3:
        if (TrailMove(a_table))
        {
            return true;
        }
    }

    return false;
}

bool Player::TrailMove(Table & a_table)
{
    int index = Console::ProcessCardPick(m_hand) - 1;

    Card card = m_hand[index];
    a_table.AddCard(card);
    m_hand.erase(m_hand.begin() + index);

    return true;
}

bool Player::BuildMove(Table & a_table)
{
    int choice = Console::ProcessBuildMenu();

    switch (choice)
    {
    case 1:
        if (CreateBuild(a_table))
        {
            return true;
        }
    case 2:
        // TODO: increase
        return false;
    case 3:
        // TODO: extend
        return false;
    }

    return false;
}

bool Player::CreateBuild(Table & a_table)
{
    int player_card_index = Console::ProcessCardPick(m_hand) - 1;
    Card player_card = m_hand.at(player_card_index);

    int table_card_index = Console::ProcessCardPick(a_table.get_cards()) - 1;
    Card table_card = a_table.get_cards().at(table_card_index);

    vector<Card> cards;
    cards.push_back(player_card);
    cards.push_back(table_card);

    Build build(cards, m_is_human);
    a_table.AddBuild(build);

    a_table.RemoveCard(table_card);

    m_hand.erase(m_hand.begin() + player_card_index);

    return true;
}

string Player::ToString()
{
    string info;

    info += "\n    Score: " + m_score;

    info += "\n    Hand:";
    for (Card card : m_hand)
    {
        info += " " + card.get_name();
    }

    info += "\n    Pile:";
    for (Card card : m_pile)
    {
        info += " " + card.get_name();
    }

    return info;
}
