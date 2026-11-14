#include "include/strategies/humanStrategy.hpp"

class HumanPlayer : Player
{
    HumanPlayer() = default;

    virtual int chooseMove(Board& board);
};