#pragma once
#include "engine.hpp"
#include <utility>
#include <iostream>
#include <algorithm>
#include <iostream>

class AI
{
    public:
        std::pair<int, int> toggle(auto& board, int movesLeft)
        {
            return nextMove(board, movesLeft);
        }

    private:
        int getCellIndex(int row, int col)
        {
            return (row * 3 + col)+1;
        }

        // evaluate current board
        int evaluate(auto& board)
        {
            // check rows
            for(int row = 0; row<3; row++)
            {
                if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
                {
                    if(board[row][0] == 'O') {return 10;}
                    else return -10;
                }
            }

            // check columns
            for(int col = 0; col < 3; col++)
            {
                if(board[0][col] == board[1][col] && board[1][col] == board[2][col])
                {
                    if(board[0][col] == 'O') {return 10;}
                    else return -10;
                }
            }

            // check diagonal
            if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
            {
                if(board[0][0] == 'O') {return 10;}
                else return -10;
            }

            // check anti-diagonal
            if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
            {
                if(board[0][2] == 'O') {return 10;}
                else return -10;
            }

            // if no player won
            return 0;
        }
};