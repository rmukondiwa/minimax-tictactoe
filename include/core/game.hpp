#pragma once
#include "board.hpp"
#include "player.hpp"

class Game{

    public:
        Game() = default;

    private:
        Board board;
        Player playerX;
        Player playerO;

};