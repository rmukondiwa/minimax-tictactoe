#pragma once
#include "minmax.hpp"

#include <array>
#include <unordered_map>
#include <utility>
#include <iostream>

class Engine
{
    public:
        using Grid = std::array<std::array<char, 3>, 3>;

        Engine() : turns(-1), movesLeft(9)
        {
            loadBoard(board);
        }
        
        Grid& getBoard() { return board; }

        int playerMove(int cellIndex)
        {
            turns++;
            char player = (turns%2) ? 'O' : 'X';
            int row = cellLocations[cellIndex].first;
            int col = cellLocations[cellIndex].second;
            board[row][col] = player;
            movesLeft -=turns;
            if(movesLeft != 0)
            {
                int aiCell = ai.toggle(board, movesLeft);
                int row = cellLocations[aiCell].first;
                int col = cellLocations[aiCell].second;
                board[row][col] = 'O';
                movesLeft--;
            }
            turns++;
            return movesLeft;
        }

    
    private:
        Grid board;
        AI ai;
        std::unordered_map<int, std::pair<int, int>> cellLocations;
        int turns;
        int movesLeft;
        
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