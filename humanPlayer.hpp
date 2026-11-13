#pragma once
#include "player.hpp"
#include "board.hpp"

class HumanPlayer : Player
{
    HumanPlayer() = default;

    virtual int chooseMove(Board& board);
};