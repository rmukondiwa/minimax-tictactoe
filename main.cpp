#include "board.hpp"

#include <iostream>
#include <vector>


namespace{

void display(auto& board)
{
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

    display(boardState);
    int playerin = 0;
    std::cin >> playerin;
    board.playerMove(playerin);
    display(boardState);

    return 0;
}