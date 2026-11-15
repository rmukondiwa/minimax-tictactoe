#pragma once
#include "player.hpp"
#include "board.hpp"

class HumanPlayer : Player
{
    public:
        HumanPlayer() = default;
        virtual int chooseMove(Board& board);
};