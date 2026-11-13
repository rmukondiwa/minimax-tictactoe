#pragma once

#include "console.hpp"

class Session{
    public:
        Session() = default;

        void runGame()
        {
            while(!gameOver)
            {
                console.display();
                int round = gamesPlayed;
                playerMove();
                checkGame();
                if(!gameOver && round == gamesPlayed)
                {
                    console.display();
                    aiMove();
                    checkGame();
                }
            }
        }

    private:
        Console console;
        
};