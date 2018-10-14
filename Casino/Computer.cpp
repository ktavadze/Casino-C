#include "pch.h"
#include "Computer.h"

int Computer::make_move(Table & a_table)
{
    // Select trail card
    Card trail_card = m_hand.get_card(0);

    if (can_trail(a_table, trail_card))
    {
        // Add trail card to table
        a_table.add_loose_card(trail_card);

        // Remove trail card from hand
        m_hand.remove_card(trail_card);
    }

    return 0;
}
