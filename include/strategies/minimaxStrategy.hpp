#pragma once
#include "player.hpp"
#include "board.hpp"

class MinimaxPlayer : Player
{
    public:
        MinimaxPlayer() = default;

        virtual int chooseMove(Board& board);

                // find best possible move
        std::pair<int, int> nextMove(auto& board, int movesLeft);

        // find optimal score using minmax algorithm
        int minimax(auto& board, int depth, bool isMax, int movesLeft);
};