#pragma once
#include <iostream>

class sudoku_checker
{
public:
    virtual bool is_valid_sudoku(const int row, const int col, const int num) const
    {
        return false;
    };

    virtual ~sudoku_checker() = default;
};

class sudoku_checker_classic final : public sudoku_checker
{
    int sudoku[9][9]{};
public:
    bool is_valid_sudoku(const int row, const int col, const int num) const override
    {
        for (int x = 0; x < 9; x++)
        {
            if (sudoku[row][x] == num)
            {
                return false;
            }
            if (sudoku[x][col] == num)
            {
                return false;
            }
            if (sudoku[row - row % 3 + x / 3][col - col % 3 + x % 3] == num)
            {
                return false;
            }
        }
        return true;
    }

};

class sudoku_checker_diagonal final : public sudoku_checker
{
    int sudoku[9][9]{};
public:

};