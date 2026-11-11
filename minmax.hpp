#pragma once

#include <utility>
#include <iostream>
#include <algorithm>
#include <iostream>

class AI
{
    public:
        int toggle(auto& board, int movesLeft)
        {
            const auto& cell = nextMove(board, movesLeft);
            int cellIndex = cell.first * 3 + cell.second;
            std::cout<<"AI wants to play cell " << cellIndex<<std::endl;
            return cellIndex;
        }
    
    private:
        // find best possible move
        std::pair<int, int> nextMove(auto& board, int movesLeft)
        {
            int bestScore = -11;
            int row = 0;
            int col = 0;
            for(int i = 0; i<3; i++)
            {
                for(int j = 0; j<3; j++)
                {
                    if(board[i][j] == 'X' || board[i][j] == 'O') continue;

                    int moveScore = minmax(board, 0, true, movesLeft);

                    if(moveScore > bestScore)
                    {
                        row = i;
                        col = j;
                    }
                }
            }

            return {row, col};
        }
        // find optimal score using minmax algorithm
        int minmax(auto& board, int depth, bool isMax, int movesLeft)
        {
            int score = evaluate(board);

            if(score == 10)
            {
                return score - depth;
            }
            else if (score == -10)
            {
                return score + depth;
            }

            if(movesLeft == 0) return 0;
            
            // the maximizing player's turn (AI)
            if (isMax)
            {
                int best = -11;
                for(int i = 0; i<3; i++)
                {
                    for(int j = 0; j<3; j++)
                    {

                        if(board[i][j] == 'O' || board[i][j] == 'X') continue;
                        board[i][j] = 'O';

                        int best = std::max(best, minmax(board, depth+1, false, movesLeft-1));
                        int cellIndex = i * 3 +j;
                        board[i][j] = cellIndex + '0';
                    }
                }

                return best;
            }
            else
            {
                int best = 11;
                for(int i = 0; i<3; i++)
                {
                    for(int j = 0; j<3; j++)
                    {

                        if(board[i][j] == 'O' || board[i][j] == 'X') continue;
                        board[i][j] = 'X';

                        int best = std::min(best, minmax(board, depth+1, true, movesLeft-1));
                        int cellIndex = i * 3 +j;
                        board[i][j] = cellIndex + '0';
                    }
                }

                return best;
            }

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