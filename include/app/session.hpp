#pragma once

#include "console.hpp"
#include "scoreboard.hpp"
#include "game.hpp"

class Session{
    public:
        Session() = default;

        void runGame();

    private:
        Console console;
        Scoreboard score;
        Game game;
};