#include "engine.hpp"
#include "minmax.hpp"

#include <iostream>
#include <vector>

int main()
{
    Engine engine;
    const auto& boardState = engine.getBoard();

    while(true)
    {
        engine.display(boardState);
        int playerin = 0;
        std::cin >> playerin;
        int movesLeft = engine.playerMove(playerin);

        if(movesLeft == 0)
        {
            std::cout<<"GAME OVER!\n";
            break;
        }
    }

    return 0;
}