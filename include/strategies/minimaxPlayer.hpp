#pragma once
#include "player.hpp"
#include "board.hpp"

class MinimaxPlayer : Player 
{
    public:
        MinimaxPlayer() = default;

        virtual int chooseMove(Board& board);

                // find best possible move
        std::pair<int, int> nextMove(auto& board, int movesLeft)
        {
            int bestScore = -1000;
            int row = 0;
            int col = 0;
            for(int i = 0; i<3; i++)
            {
                for(int j = 0; j<3; j++)
                {
                    if(board[i][j] == 'X' || board[i][j] == 'O') continue;

                    board[i][j] = 'O';
                    int moveScore = minimax(board, 0, false, movesLeft-1);
                    if(moveScore > bestScore)
                    {
                        row = i;
                        col = j;
                        bestScore = moveScore;
                    }
                    board[i][j] =  getCellIndex(i, j) + '0';
                }
            }
            return {row, col};
        }

        // find optimal score using minmax algorithm
        int minimax(auto& board, int depth, bool isMax, int movesLeft)
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
                int best = -1000;
                for(int i = 0; i<3; i++)
                {
                    for(int j = 0; j<3; j++)
                    {
                        if(board[i][j] == 'O' || board[i][j] == 'X') continue;
                        board[i][j] = 'O';
                        best = std::max(best, minimax(board, depth+1, false, movesLeft-1));
                        board[i][j] = getCellIndex(i, j) + '0';
                    }
                }
                return best;
            }
            else
            {
                int best = 1000;
                for(int i = 0; i<3; i++)
                {
                    for(int j = 0; j<3; j++)
                    {
                        if(board[i][j] == 'O' || board[i][j] == 'X') continue;
                        board[i][j] = 'X';
                        best = std::min(best, minimax(board, depth+1, true, movesLeft-1));
                        board[i][j] = getCellIndex(i,j) + '0';
                    }
                }
                return best;
            }
        }
};