#pragma once

#include "minimax.hpp"

#include <array>
#include <unordered_map>
#include <iostream>

class Engine
{
    public:
        Engine() : turns(0), movesLeft(9), gamesPlayed(1), humanWins(0), computerWins(0), gameOver(false), draws(0)
        {
            loadBoard();
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
        using Grid = std::array<std::array<char, 3>, 3>;
        Grid board;
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
            if (movesLeft>0 && !hasWinner().first)
            {
                gameOver = false;
            }
            else
            {
                display();
                char player =hasWinner().second;
                if(player == '\0') draws++;
                printWinner(player);
                if(continuing())
                {
                    gamesPlayed++;
                    loadBoard();
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

        void loadBoard()
        {
            turns = 0;
            movesLeft = 9;
            gameOver = false;
            for(int row = 0; row<3; row++)
            {
                for(int col = 0; col<3; col++)
                {
                    int cellIndex = getCellIndex(row, col);
                    board[row][col] = (cellIndex)+'0';
                }
            }
        }

        int getCellIndex(int row, int col)
        {
            return (row * 3 + col)+1;
        }

        std::pair<int, int> toRowCol(int cellIndex)
        {
            return {(cellIndex-1)/3, (cellIndex-1)%3};
        }

        void playerMove()
        {
            int cellIndex = 0;  // declaring this guarantees predictable fall back
            std::cin >> cellIndex;
            char player = (turns%2) ? 'O' : 'X';
            auto [row, col] = toRowCol(cellIndex);
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

        std::pair<bool, char> hasWinner()
        {
             // check rows
            for(int row = 0; row<3; row++)
            {
                if (board[row][0] == board[row][1]
                    && board[row][1] == board[row][2])
                {
                    return {true, board[row][0]};
                }
            }

            // check columns
            for(int col = 0; col < 3; col++)
            {
                if(board[0][col] == board[1][col]
                    && board[1][col] == board[2][col])
                {
                    return {true, board[0][col]};
                }
            }

            // check diagonal
            if(board[0][0] == board[1][1]
                && board[1][1] == board[2][2])
            {
                return {true, board[0][0]};
            }

            // check anti-diagonal
            if(board[0][2] == board[1][1]
                && board[1][1] == board[2][0])
            {
                return {true, board[0][2]};
            }

            // no winner
            return {false,'\0'};
        }
};