#pragma once
#include "board.hpp"

class Player
{
    Player() = default;

    virtual int chooseMove(Board& board);
};