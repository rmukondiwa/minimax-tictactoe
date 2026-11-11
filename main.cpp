#include "engine.hpp"
#include "minmax.hpp"

#include <iostream>
#include <vector>

int main()
{
    Engine engine;

    while(true)
    {
        engine.display();
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