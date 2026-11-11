#pragma once

#include <array>
#include <unordered_map>
#include <pair>

class Board
{
    public:
        using Grid = std::array<std::array<int, 3>, 3>;

        Board() : turns(-1)
        {
            loadBoard(board);
        }
        
        Grid getBoard() { return board; }

        Grid playerMove(int cell)
        {
            turns++;
            char player = (turns%2) ? 'O' : 'X';

            Grid
        }

    
    private:
        Grid board;
        std::unordered_map<int, std::pair<int, int>> cellLocations;
        int turns;
        
        void loadBoard(Grid&  board)
        {
            for(int row = 0; row<3; row++)
            {
                for(int col = 0; col<3; col++)
                {
                    int cellIndex = row * 3 + col;
                    board[row][col] = cellIndex;

                    cellLocations[cellIndex] = {row, col};
                }
            }
        }

        
};