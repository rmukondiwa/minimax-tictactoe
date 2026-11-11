#pragma once

#include <array>
#include <unordered_map>
#include <utility>
#include <iostream>

class Board
{
    public:
        using Grid = std::array<std::array<char, 3>, 3>;

        Board() : turns(-1)
        {
            loadBoard(board);
        }
        
        Grid& getBoard() { return board; }

        void playerMove(int cellIndex)
        {
            turns+=2;
            char player = (turns%2) ? 'O' : 'X';
            int row = cellLocations[cellIndex].first;
            int col = cellLocations[cellIndex].second;
            board[row][col] = player;
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
                    board[row][col] = (cellIndex)+'0';

                    cellLocations[cellIndex] = {row, col};
                }
            }
        }

        
};