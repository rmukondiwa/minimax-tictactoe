#pragma once
#include "board.hpp"

class Player
{
    public:
        Player() = default;
        int chooseMove(const Board& board);
};