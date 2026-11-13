#pragma once

#include "minimax.hpp"
#include "board.hpp"

#include <iostream>

class Engine
{
    public:
        Engine() : turns(0), movesLeft(9), gamesPlayed(1), humanWins(0), computerWins(0), gameOver(false), draws(0)
        {
            board.loadBoard();
        }

    private:
        Board board;
        AI ai;
        int turns;
        int movesLeft;
        int gamesPlayed;
        int humanWins;
        int computerWins;
        bool gameOver;
        int draws;

        bool checkGame()
        {
            if (movesLeft>0 && !board.hasWinner().first)
            {
                gameOver = false;
            }
            else
            {
                display();
                char player = board.hasWinner().second;
                if(player == '\0') draws++;
                printWinner(player);
                if(continuing())
                {
                    gamesPlayed++;
                    board.loadBoard();
                }
                else
                {
                    gameOver = true;
                    displaySummary(player);
                }
            }

            return gameOver;
        }

        void playerMove()
        {
            int cellIndex = 0;  // declaring this guarantees predictable fall back
            std::cin >> cellIndex;
            char player = (turns%2) ? 'O' : 'X';
            auto [row, col] = board.toRowCol(cellIndex);
            board[row][col] = player;
            turns++;
            movesLeft--;
        }

        void aiMove()
        {
            char player = (turns%2) ? 'O' : 'X';
            auto [row, col] = ai.toggle(board, movesLeft);
            board[row][col] = player;
            movesLeft--;
            turns++;
        }

        double winRate() const
        {
            return (static_cast<double>(humanWins) / gamesPlayed)*100;
        }
};