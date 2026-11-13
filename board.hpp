#pragma once
#include <array>

class Board
{
    public:
        int getCellIndex(int row, int col)
        {
            return (row * 3 + col)+1;
        }

        std::pair<int, int> toRowCol(int cellIndex)
        {
            return {(cellIndex-1)/3, (cellIndex-1)%3};
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

        void loadBoard()
        {
            for(int row = 0; row<3; row++)
            {
                for(int col = 0; col<3; col++)
                {
                    int cellIndex = getCellIndex(row, col);
                    board[row][col] = (cellIndex)+'0';
                }
            }
        }

    private:
        using Grid = std::array<std::array<char, 3>, 3>;
        Grid board;
};