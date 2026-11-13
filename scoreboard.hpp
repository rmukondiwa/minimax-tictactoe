#pragma once

class Scoreboard{
    public:
        int gamesPlayed;

        Scoreboard() = default;

        double winRate() const
        {
            return (static_cast<double>(humanWins) / gamesPlayed)*100;
        }

        void record(GameStatus& result);

    private:
        int humanWins;
        int computerWins;
        int draws;
};