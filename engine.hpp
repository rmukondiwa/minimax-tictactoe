#pragma once
#include "minmax.hpp"

#include <array>
#include <unordered_map>
#include <utility>
#include <iostream>

class Engine
{
    public:
        Engine() : turns(-1), movesLeft(9), gamesPlayed(1), playerWins(0)
        {
            loadBoard();
        }
        
        bool newGame()
        {
            while(true)
            {
                display();
                int playerin = 0;
                std::cin >> playerin;
                int movesLeft = playerMove(playerin);

                if(movesLeft == 0)
                {
                    std::cout<<"Continue?[y] End?[n]\n";
                    char endGame;
                    std::cin >> endGame;

                    if(endGame == 'n' || endGame == 'N')
                    {
                        displaySummary();
                        break;
                    }
                    else
                    {
                        loadBoard();
                        gamesPlayed++;
                        playerWins += wonGame() ? 1 : 0;
                    }
                    
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
        int playerWins;

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

        void displaySummary()
        {
            std::cout<<"\nSession Ended:\nSummary:\n";

            std::cout<<"Games played: " << gamesPlayed << "\n";
            std::cout<<"Your wins: " << playerWins << "\n";
            std::cout<<"Your losses: " << gamesPlayed-playerWins << "\n";
            std::cout<<"Winning %: " << winRate() << "\n";
            for(auto& row : board)
            {
                std::cout<<row[0] << "|"<<row[1]<<"|"<<row[2]<<"\n";
                // TODO: figure out horizontal bars
            }
        }
        
        void loadBoard()
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

        int playerMove(int cellIndex)
        {
            turns++;
            char player = (turns%2) ? 'O' : 'X';
            int row = cellLocations[cellIndex].first;
            int col = cellLocations[cellIndex].second;
            board[row][col] = player;
            movesLeft--;
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

        const double winRate()
        {
            return static_cast<double>(playerWins) / gamesPlayed;
        }

        bool wonGame()
        {
             // check rows
            for(int row = 0; row<3; row++)
            {
                if ((board[row][0] == board[row][1] 
                    && board[row][1] == board[row][2])
                    && board[row][0] == 'X')
                {
                    return true;
                }
            }

            // check columns
            for(int col = 0; col < 3; col++)
            {
                if((board[0][col] == board[1][col] 
                    && board[1][col] == board[2][col])
                    && board[0][col] == 'X')
                {
                    return true;
                }
            }

            // check diagonal
            if((board[0][0] == board[1][1] 
                && board[1][1] == board[2][2])
                && board[0][0] == 'X')
            {
                return true;
            }

            // check anti-diagonal
            if((board[0][2] == board[1][1] 
                && board[1][1] == board[2][0])
                && board[0][2] == 'X')
            {
                return true;
            }

            // player lost
            return false;
        }

        
};