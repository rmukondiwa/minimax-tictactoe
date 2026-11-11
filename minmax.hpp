#pragma once
#include "board.hpp"

#include <utility>
#include <iostream>

class AI
{
    public:
        // find best possible move
        std::pair<int, int> nextMove(auto& board)
        {
            int bestScore = -11;
            int row = 0;
            int col = 0;
            for(int i = 0; i<3; i++)
            {
                for(int j = 0; j<3; j++)
                {
                    if(board[i][j] == 'X' || board[i][j] == '0') continue;

                    int moveScore = minmax(board, 0, false);

                    if(moveScore > bestScore)
                    {
                        row = i;
                        col = j;
                    }
                }
            }

            return {row, col};
        }
    
    private:
        
        // find optimal score using minmax algorithm
        int minmax(auto& board, int depth, bool isMax)
        {

            int score = evaluate(board);

            if(score == 10)
            {
                std::cout<<"ai lost!\n";
                return score - depth;
            }
            else if (score == -10)
            {
                return score + depth;
            }

        }

        // evaluate current board
        int evaluate(auto& board)
        {
            // check rows
            for(int row = 0; row<3; row++)
            {
                if (board[row][0] == board[row][1] && board[row][1] == board[row][0])
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