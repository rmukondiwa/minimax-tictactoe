#pragma once

#include <iostream>

class Console
{
    public:
        Console() = default;

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

        int readCell(Board& board);
};