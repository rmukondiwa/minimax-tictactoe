#include "board.hpp"

#include <iostream>
#include <vector>


namespace{

void display(auto& board)
{
    for(auto& row : board)
    {
        int col0 = row[0];
        int col1 = row[1];
        int col2 = row[2];
        std::cout<<col0 << "|"<<col1<<"|"<<col2<<"\n";
    }
}
}

int main(int argc, const char* argv)
{
    Board board;
    const auto& boardState = board.getBoard();

    while(true)
    {
        display(boardState);
    }

    return 0;
}