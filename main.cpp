#include "board.hpp"
#include "minmax.hpp"

#include <iostream>
#include <vector>


namespace{

void display(auto& board)
{
    std::cout<<"\n Your Turn:\n";
    for(auto& row : board)
    {
        std::cout<<row[0] << "|"<<row[1]<<"|"<<row[2]<<"\n";
        // TODO: figure out horizontal bars
    }
}
}

int main(int argc, char** argv)
{
    Board board;
    const auto& boardState = board.getBoard();
    AI ai;

    for(int i = 0; i<3; i++)
    {
        display(boardState);
        int playerin = 0;
        std::cin >> playerin;
        board.playerMove(playerin);
        display(boardState);
    }
    ai.nextMove(boardState);

    return 0;
}