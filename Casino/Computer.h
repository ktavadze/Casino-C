#pragma once

#include "Player.h"

class Computer : public Player
{
public:
    Computer() {}
    virtual void Play(Table& a_table);
    virtual bool MakeMove(Table& a_table);
    virtual bool Trail(Table& a_table);
};
