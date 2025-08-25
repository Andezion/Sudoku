#pragma once
#include <array>
#include "sudoku_checker.h"

class sudoku_solver
{
protected:
    const sudoku_checker & checker;
public:
    explicit sudoku_solver(const sudoku_checker& checker)
        : checker(checker) {}

    virtual bool solve(std::array<std::array<int, 9>, 9> & sudoku) const = 0;
    virtual ~sudoku_solver() = default;
};

class sudoku_solver_classic final : public sudoku_solver
{
public:
    explicit sudoku_solver_classic(const sudoku_checker& checker)
        : sudoku_solver(checker) {}

    bool solve(std::array<std::array<int, 9>, 9> & sudoku) const override
    {
        int row{}, col{};
        bool changed = true;

        for (row = 0; row < 9; row++)
        {
            for (col = 0; col < 9; col++)
            {
                if (sudoku[row][col] == 0)
                {
                    changed = false;
                    break;
                }
            }
            if (!changed)
            {
                break;
            }
        }

        if (changed)
        {
            return true;
        }

        for (int num = 1; num <= 9; num++)
        {
            if (checker.is_valid_sudoku(sudoku, row, col, num))
            {
                sudoku[row][col] = num;

                if (solve(sudoku))
                {
                    return true;
                }

                sudoku[row][col] = 0;
            }
        }

        return false;
    }
};