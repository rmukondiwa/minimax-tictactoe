#pragma once

#include "minimax.hpp"

#include <array>
#include <unordered_map>
#include <iostream>

class Engine
{
    public:
        Engine() : turns(0), movesLeft(9), gamesPlayed(0), humanWins(0), gameOver(false)
        {
            loadBoard();
            loadCellLocations();
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
        std::unordered_map<int, std::pair<int, int>> cellLocations;
        int turns;
        int movesLeft;
        int gamesPlayed;
        int humanWins;
        bool gameOver;

        void display()
        {
            std::cout<<"\nGame Session: \n" << gamesPlayed;
            std::cout<<"\nYour Turn:\n";
            for(auto& row : board)
            {
                std::cout<<row[0] << "|"<<row[1]<<"|"<<row[2]<<"\n";
                // TODO: figure out horizontal bars
            }
        }

        char getCell(char cellIndex)
        {
            int row = cellLocations[cellIndex].first;
            int col = cellLocations[cellIndex].second;

            return board[row][col];
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
                char player = getCell(hasWinner().second);
                humanWins += ( player== 'X') ? 1 : 0;
                printWinner(player);
                if(continuing())
                {
                    gamesPlayed++;
                    loadBoard();
                }
                else
                {
                    gamesPlayed++;
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
            std::cout<<"Games played: " << gamesPlayed << "\n";
            std::cout<<"Your wins: " << humanWins << "\n";
            std::cout<<"Your losses: " << gamesPlayed-humanWins << "\n";
            std::cout<<"Winning Rate: " << winRate() << "%\n";
            for(auto& row : board)
            {
                std::cout<<row[0] << "|"<<row[1]<<"|"<<row[2]<<"\n";
                // TODO: figure out horizontal bars
            }
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
                    int cellIndex = row * 3 + col;
                    board[row][col] = (cellIndex)+'0';
                }
            }
        }

        void loadCellLocations()
        {
            for(int row = 0; row<3; row++)
            {
                for(int col = 0; col<3; col++)
                {
                    int cellIndex = row * 3 + col;
                    cellLocations[cellIndex] = {row, col};
                }
            }
        }

        void playerMove()
        {
            int cellIndex = 0;  // declaring this guarantees predictable fall back
            std::cin >> cellIndex;
            char player = (turns%2) ? 'O' : 'X';
            int row = cellLocations[cellIndex].first;
            int col = cellLocations[cellIndex].second;
            board[row][col] = player;
            turns++;
            movesLeft--;
        }

        void aiMove()
        {
            char player = (turns%2) ? 'O' : 'X';
            int aiCell = ai.toggle(board, movesLeft);
            int row = cellLocations[aiCell].first;
            int col = cellLocations[aiCell].second;
            board[row][col] = player;
            movesLeft--;
            turns++;
        }

        double winRate() const
        {
            return (static_cast<double>(humanWins) / gamesPlayed)*100;
        }

        std::pair<bool, int> hasWinner()
        {
             // check rows
            for(int row = 0; row<3; row++)
            {
                if (board[row][0] == board[row][1]
                    && board[row][1] == board[row][2])
                {
                    return {true, row*3};
                }
            }

            // check columns
            for(int col = 0; col < 3; col++)
            {
                if(board[0][col] == board[1][col]
                    && board[1][col] == board[2][col])
                {
                    return {true, col};
                }
            }

            // check diagonal
            if(board[0][0] == board[1][1]
                && board[1][1] == board[2][2])
            {
                return {true, 0};
            }

            // check anti-diagonal
            if(board[0][2] == board[1][1]
                && board[1][1] == board[2][0])
            {
                return {true, 2};
            }

            // player lost
            return {false,-1};
        }
};