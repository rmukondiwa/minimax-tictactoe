#include "engine.hpp"
#include "minmax.hpp"

#include <iostream>
#include <vector>


namespace{

void display(auto& board)
{
    std::cout<<"\nYour Turn:\n";
    for(auto& row : board)
    {
        std::cout<<row[0] << "|"<<row[1]<<"|"<<row[2]<<"\n";
        // TODO: figure out horizontal bars
    }
}
}

int main()
{
    Engine engine;
    const auto& boardState = engine.getBoard();

    while(true)
    {
        display(boardState);
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