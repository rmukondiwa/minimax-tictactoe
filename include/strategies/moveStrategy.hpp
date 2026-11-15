#include "include/core/board.hpp"

class MoveStrategy{
    public:
        MoveStrategy() = default;
        virtual int chooseMove(Board& board);

};