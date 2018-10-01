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
        return BuildMove(a_table);
    case 2:
        // TODO: capture
        return false;
    case 3:
        return TrailMove(a_table);
    default:
        return false;
    }
}

bool Player::TrailMove(Table & a_table)
{
    int index = Console::PickPlayerCard(m_hand) - 1;
    Card card = m_hand.Get(index);

    if (CanPlay(a_table, card))
    {
        a_table.AddCard(card);

        m_hand.RemoveCard(card);

        return true;
    }

    return false;
}

bool Player::BuildMove(Table & a_table)
{
    int choice = Console::ProcessBuildMenu();

    switch (choice)
    {
    case 1:
        return CreateBuild(a_table);
    case 2:
        // TODO: increase
        return false;
    case 3:
        // TODO: extend
        return false;
    default:
        return false;
    }
}

bool Player::CreateBuild(Table & a_table)
{
    if (a_table.get_cards().Empty())
    {
        return false;
    }

    Set selected_cards;

    // Select player card
    int player_card_index = Console::PickPlayerCard(m_hand) - 1;
    Card player_card = m_hand.Get(player_card_index);
    selected_cards.AddCard(player_card);

    // Select loose cards
    Set loose_cards = Console::PickLooseCards(a_table.get_cards());
    for (Card card : loose_cards.get_cards())
    {
        selected_cards.AddCard(card);
    }

    Build build(m_is_human, selected_cards);

    for (Card card : m_hand.get_cards())
    {
        if (card.get_value() == build.get_value())
        {
            if (CanPlay(a_table, player_card))
            {
                a_table.AddBuild(build);

                for (Card loose_card : loose_cards.get_cards())
                {
                    a_table.RemoveCard(loose_card);
                }

                m_hand.RemoveCard(player_card);

                return true;
            }
        }
    }

    return false;
}

bool Player::CanPlay(Table a_table, Card a_card)
{
    for (Build build : a_table.get_builds())
    {
        if (build.get_value() == a_card.get_value() && build.is_human() == m_is_human)
        {
            int count = 0;

            for (Card card : m_hand.get_cards())
            {
                if (card.get_value() == a_card.get_value())
                {
                    count++;
                }
            }

            if (count < 2)
            {
                return false;
            }
        }
    }

    return true;
}

string Player::ToString()
{
    string info;

    info += "\n    Score: " + m_score;

    info += "\n    Hand: " + m_hand.ToString();

    info += "\n    Pile: " + m_pile.ToString();

    return info;
}
