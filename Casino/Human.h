#pragma once

#include "Player.h"

class Human : public Player
{
public:
    Human() {}
    virtual void Play(Table& a_table);
};
