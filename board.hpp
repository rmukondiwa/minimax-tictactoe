#pragma once

#include <array>

class Board
{
    public:
        Board()
        {
            loadBoard(board);
        }

        std::array<std::array<int, 3>, 3> getBoard() { return board; }
    
    private:
        std::array<std::array<int, 3>, 3> board;
        
        void loadBoard(std::array<std::array<int, 3>, 3>&  board)
        {
            for(int row = 0; row<3; row++)
            {
                for(int col = 0; col<3; col++)
                {
                    board[row][col] = row * 3 + col;
                }
            }
        }

        
};