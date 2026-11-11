#pragma once

#include <array>

class Board
{
    public:
        using Grid = std::array<std::array<int, 3>, 3>;

        Board() : turns(0)
        {
            loadBoard(board);
        }
        
        Grid getBoard() { return board; }

        

    
    private:
        Grid board;
        int turns;
        
        void loadBoard(Grid&  board)
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