#pragma once

#include "minmax.hpp"

#include <array>
#include <unordered_map>
#include <iostream>

class Engine
{
    public:
        Engine() : turns(0), movesLeft(9), gamesPlayed(1), humanWins(0)
        {
            loadBoard();
            loadCellLocations();
        }

        void runGame()
        {
            display();
            while(checkGame())
            {
                playerMove();
                display();
                if(checkGame())
                {
                    aiMove();
                    display();
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
                return true;
            }
            else
            {
                gamesPlayed++;
                humanWins += (getCell(hasWinner().second) == 'X') ? 1 : 0;
                if(continuing())
                {
                    loadBoard();
                    return true;
                }
                else
                {
                    displaySummary(getCell(hasWinner().second));
                    return false;
                }
            }
        }

        void displaySummary(char player)
        {
            if(player == 'X')
            {
                std::cout<<"\nHuman wins!";
            }
            else if (player == 'O')
            {
                std::cout<<"\nComputer wins!";
            }
            else
            {
                std::cout<<"\nDRAW!";
            }

            std::cout<<" \nSummary:\n";
            std::cout<<"Games played: " << gamesPlayed << "\n";
            std::cout<<"Your wins: " << humanWins << "\n";
            std::cout<<"Your losses: " << gamesPlayed-humanWins << "\n";
            std::cout<<"Winning %: " << winRate() << "\n";
            for(auto& row : board)
            {
                std::cout<<row[0] << "|"<<row[1]<<"|"<<row[2]<<"\n";
                // TODO: figure out horizontal bars
            }
        }

        void loadBoard()
        {
            turns = 0;
            movesLeft = 9;
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
            int cellIndex = 0;
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
            return static_cast<double>(humanWins) / gamesPlayed;
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