#pragma once

#include "types.hpp"

class Scoreboard{
    public:
        int gamesPlayed;

        Scoreboard() = default;

        double winRate() const;

        void record(GameStatus& result);

    private:
        int humanWins;
        int computerWins;
        int draws;
};