#include "pch.h"
#include "Computer.h"

/**********************************************************************
Function Name: make_move
Purpose: To allow the computer (virtual) to make a move
Parameters:
    a_table, a Table instance passed by reference
Return Value: The move code associated with made move, an integer value
    (1 = capture; 0 = build/trail)
**********************************************************************/
int Computer::make_move(Table & a_table)
{
    if (can_increase(a_table))
    {
        process_increase_build(a_table);
    }
    else if (can_extend(a_table))
    {
        process_extend_build(a_table);
    }
    else if (can_create(a_table))
    {
        process_create_build(a_table);
    }
    else if (can_capture(a_table))
    {
        process_capture(a_table);

        return 1;
    }
    else {
        process_trail(a_table);
    }

    return 0;
}

/**********************************************************************
Function Name: process_increase_build
Purpose: To allow the computer to increase the best existing build
Parameters:
    a_table, a Table instance passed by reference
**********************************************************************/
void Computer::process_increase_build(Table & a_table)
{
    Build best_build = find_best_increase(a_table);

    increase_build(a_table, best_build);
}

/**********************************************************************
Function Name: process_extend_build
Purpose: To allow the computer to extend the best existing build
Parameters:
    a_table, a Table instance passed by reference
**********************************************************************/
void Computer::process_extend_build(Table & a_table)
{
    Build best_build = find_best_extend(a_table);

    extend_build(a_table, best_build);
}

/**********************************************************************
Function Name: process_extend_build
Purpose: To allow the computer to create the best new build
Parameters:
    a_table, a Table instance passed by reference
**********************************************************************/
void Computer::process_create_build(Table & a_table)
{
    Build best_build = find_best_create(a_table);

    create_build(a_table, best_build);
}

/**********************************************************************
Function Name: process_capture
Purpose: To allow the computer to capture the best set
Parameters:
    a_table, a Table instance passed by reference
**********************************************************************/
void Computer::process_capture(Table & a_table)
{
    Set best_capture_set = find_best_caputre(a_table);

    capture(a_table, best_capture_set);
}

/**********************************************************************
Function Name: process_trail
Purpose: To allow the computer to trail the best card
Parameters:
    a_table, a Table instance passed by reference
**********************************************************************/
void Computer::process_trail(Table & a_table)
{
    Card best_trail_card = find_best_trail(a_table);

    trail(a_table, best_trail_card);
}

/**********************************************************************
Function Name: increase_build
Purpose: To allow the computer to increase specified build
Parameters:
    a_table, a Table instance passed by reference
    a_build, a Build instance passed by value. Represents the increased build
**********************************************************************/
void Computer::increase_build(Table & a_table, Build a_build)
{
    Set build_set = a_build.get_sets().at(0);

    // Remove player card from hand
    m_hand.remove_card(build_set.get_last_card());

    // Increase build
    for (unsigned int i = 0; i < a_table.get_builds().size(); i++)
    {
        Build build = a_table.get_builds().at(i);

        if (build_set.contains(build.get_sets()))
        {
            a_table.increase_build(i, build_set.get_last_card(), m_is_human);
        }
    }
}

/**********************************************************************
Function Name: extend_build
Purpose: To allow the computer to extend specified build
Parameters:
    a_table, a Table instance passed by reference
    a_build, a Build instance passed by value. Represents the extended build
**********************************************************************/
void Computer::extend_build(Table & a_table, Build a_build)
{
    Set build_set = a_build.get_sets().at(a_build.get_sets().size() - 1);

    // Remove player card from hand
    m_hand.remove_card(build_set.get_first_card());

    // Remove loose set from table
    for (Card card : a_table.get_loose_set().get_cards())
    {
        if (build_set.contains(card))
        {
            a_table.remove_loose_card(card);
        }
    }

    Set extended_set;

    for (Build build : a_table.get_builds())
    {
        for (Set set : build.get_sets())
        {
            extended_set.add_set(set);
        }
    }

    // Extend build
    for (unsigned int i = 0; i < a_table.get_builds().size(); i++)
    {
        Build build = a_table.get_builds().at(i);

        if (extended_set.contains(build.get_sets()))
        {
            a_table.extend_build(i, build_set, m_is_human);
        }
    }
}

/**********************************************************************
Function Name: create_build
Purpose: To allow the computer to create specified build
Parameters:
    a_table, a Table instance passed by reference
    a_build, a Build instance passed by value. Represents the created build
**********************************************************************/
void Computer::create_build(Table & a_table, Build a_build)
{
    Set build_set = a_build.get_sets().at(0);

    // Remove player card from hand
    m_hand.remove_card(build_set.get_first_card());

    // Remove loose set from table
    for (Card card : a_table.get_loose_set().get_cards())
    {
        if (build_set.contains(card))
        {
            a_table.remove_loose_card(card);
        }
    }

    // Add build to table
    a_table.add_build(a_build);
}

/**********************************************************************
Function Name: capture
Purpose: To allow the computer to capture specified set
Parameters:
    a_table, a Table instance passed by reference
    a_capture_set, a Set instance passed by value
**********************************************************************/
void Computer::capture(Table & a_table, Set a_capture_set)
{
    // Remove capture card from hand
    m_hand.remove_card(a_capture_set.get_first_card());

    // Add capture card to pile
    m_pile.add_card(a_capture_set.get_first_card());

    // Capture loose set
    for (Card card : a_table.get_loose_set().get_cards())
    {
        if (a_capture_set.contains(card))
        {
            capture_loose_card(a_table, card);
        }
    }

    // Capture builds
    for (Build build : a_table.get_builds())
    {
        if (a_capture_set.contains(build.get_sets()))
        {
            capture_build(a_table, build);
        }
    }
}

/**********************************************************************
Function Name: trail
Purpose: To allow the computer to trail specified card
Parameters:
    a_table, a Table instance passed by reference
    a_trail_card, a Card instance passed by value
**********************************************************************/
void Computer::trail(Table & a_table, Card a_trail_card)
{
    // Remove trail card from hand
    m_hand.remove_card(a_trail_card);

    // Add trail card to table
    a_table.add_loose_card(a_trail_card);
}
