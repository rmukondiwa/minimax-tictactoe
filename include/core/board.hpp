#pragma once
#include <array>

class Board
{
    public:
        int getCellIndex(int row, int col);

        std::pair<int, int> toRowCol(int cellIndex);

        std::pair<bool, char> hasWinner();

        void loadBoard();

    private:
        using Grid = std::array<std::array<char, 3>, 3>;
        Grid board;
};