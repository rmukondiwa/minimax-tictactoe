#pragma once
#include "minmax.hpp"

#include <array>
#include <unordered_map>
#include <utility>
#include <iostream>

class Engine
{
    public:
        using Grid = std::array<std::array<char, 3>, 3>;

        Engine() : turns(-1), movesLeft(9)
        {
            loadBoard(board);
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

                    if(endGame == 'n')
                    {
                        displaySummary();
                        break;
                    }
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

    private:
        Grid board;
        AI ai;
        std::unordered_map<int, std::pair<int, int>> cellLocations;
        int turns;
        int movesLeft;

        void display()
        {
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
            std::cout<<"Your losses: " << playerLosses << "\n";
            std::cout<<"Winning %: " << winRate() << "\n";
            for(auto& row : board)
            {
                std::cout<<row[0] << "|"<<row[1]<<"|"<<row[2]<<"\n";
                // TODO: figure out horizontal bars
            }
        }
        
        void loadBoard(Grid&  board)
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

        
};