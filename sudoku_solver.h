#pragma once
#include <array>
#include <chrono>
#include "sudoku_checker.h"

class sudoku_solver
{
protected:
    const sudoku_checker & checker;
    mutable std::size_t stepsCount = 0;
    mutable double lastSolveMs = 0.0;
public:
    explicit sudoku_solver(const sudoku_checker& checker)
        : checker(checker) {}

    virtual bool solve(std::array<std::array<int, 9>, 9> & sudoku) const
    {
        return false;
    };
    virtual bool solve(std::array<std::array<int, 16>, 16> & sudoku) const
    {
        return false;
    };
    virtual bool solve(std::array<std::array<int, 21>, 21> & sudoku) const
    {
        return false;
    };
    virtual ~sudoku_solver() = default;

    template<typename Board>
    bool solve_with_stats(Board & sudoku) const
    {
        stepsCount = 0;

        const auto t0 = std::chrono::steady_clock::now();
        const bool res = solve(sudoku);
        const auto t1 = std::chrono::steady_clock::now();

        lastSolveMs = std::chrono::duration<double, std::milli>(t1 - t0).count();
        return res;
    }

    std::size_t get_last_steps() const
    {
        return stepsCount;
    }
    double get_last_time_ms() const
    {
        return lastSolveMs;
    }
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
                ++stepsCount;
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

class sudoku_solver_diagonal final : public sudoku_solver
{
public:
    explicit sudoku_solver_diagonal(const sudoku_checker& checker)
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
                ++stepsCount;
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

class sudoku_solver_big final : public sudoku_solver
{
public:
    explicit sudoku_solver_big(const sudoku_checker& checker)
        : sudoku_solver(checker) {}

    bool solve(std::array<std::array<int, 16>, 16> & sudoku) const override
    {
        int row{}, col{};
        bool changed = true;

        for (row = 0; row < 16; row++)
        {
            for (col = 0; col < 16; col++)
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

        for (int num = 1; num <= 16; num++)
        {
            if (checker.is_valid_sudoku(sudoku, row, col, num))
            {
                ++stepsCount;
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

class sudoku_solver_samurai final : public sudoku_solver
{
public:
    explicit sudoku_solver_samurai(const sudoku_checker& checker)
        : sudoku_solver(checker) {}

    bool solve(std::array<std::array<int, 21>, 21> & sudoku) const override
    {
        int row = -1, col = -1;
        bool found_empty = false;

        for (int i = 0; i < 21 && !found_empty; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    row = i;
                    col = j;
                    found_empty = true;
                    break;
                }
            }
        }

        if (!found_empty)
        {
            return true;
        }

        for (int num = 1; num <= 9; num++)
        {
            if (checker.is_valid_sudoku(sudoku, row, col, num))
            {
                ++stepsCount;
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