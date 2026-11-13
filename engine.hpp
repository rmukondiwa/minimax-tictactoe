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

        void runGame()
        {
            while(!gameOver)
            {
                display();
                int round = gamesPlayed;
                playerMove();
                checkGame();
                if(!gameOver && round == gamesPlayed)
                {
                    display();
                    aiMove();
                    checkGame();
                }
            }
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

        void display()
        {
            std::cout<<"\nGame Session: " << gamesPlayed<<"\n";
            if(turns%2 ==0) std::cout<<"Your Turn!\n";
            else std::cout<<"Computer Turn!\n";

            for(int i =0; i<3; i++)
            {
                auto& row = board[i];
                std::cout<<" " <<row[0] << " | "<<row[1]<<" | "<<row[2]<<"\n";
                
                if(i+1<3)
                {
                    std::cout<<"---+---+---\n";
                }
            }
        }

        bool continuing()
        {
            std::cout<<"Continue?: Yes[y] No[n]\n";
            char endGame;
            std::cin >> endGame;
            
            return endGame == 'y' || endGame == 'Y';
        }

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

        void displaySummary(char player)
        {
            printWinner(player);
            std::cout<<" \nSummary:\n";
            std::cout<<"Games played: " << gamesPlayed-1 << "\n";
            std::cout<<"Your wins: " << humanWins << "\n";
            std::cout<<"Your losses: " << gamesPlayed-(humanWins+draws)<< "\n";
            std::cout<<"Your Draws: " << draws << "\n";
            std::cout<<"Winning Rate: " << winRate() << "%\n";
            display();
        }

        void printWinner(char player)
        {
            if(player == 'X')
            {
                std::cout<<"\nHuman wins!\n";
            }
            else if (player == 'O')
            {
                std::cout<<"\nComputer wins!\n";
            }
            else
            {
                std::cout<<"\nDRAW!\n";
            }
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