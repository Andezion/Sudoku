#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>

#include "sudoku_checker.h"

class sudoku_generator
{
protected:
    const sudoku_checker & checker;
public:
    explicit sudoku_generator(const sudoku_checker& checker)
        : checker(checker) {}

    virtual void deleter(uint8_t level) {}
    virtual std::array<std::array<int, 9>, 9> generate(const uint8_t level)
    {
        return {};
    }
    virtual bool solve_sudoku(int &solutions, const int limit = 2) { return false; }

    virtual ~sudoku_generator() {}
};

class sudoku_generator_classic final : public sudoku_generator
{
    std::array<std::array<int, 9>, 9> sudoku{};
public:
    explicit sudoku_generator_classic(const sudoku_checker& checker)
        : sudoku_generator(checker) {}

    static bool create_sudoku(int i, int j, std::vector<int> probability[9][9], std::array<std::array<int, 9>, 9> & sudoku)
    {
        if (j == 9)
        {
            j = 0;
            i++;
        }
        if (i == 9)
        {
            return true;
        }

        if (sudoku[i][j] != 0)
        {
            return create_sudoku(i, j + 1, probability, sudoku);
        }

        std::vector<int> candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        for (int col = 0; col < 9; col++)
        {
            candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[i][col]), candidates.end());
        }

        for (int row = 0; row < 9; row++)
        {
            candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[row][j]), candidates.end());
        }

        const int start_i = i / 3 * 3;
        const int start_j = j / 3 * 3;
        for (int r = start_i; r < start_i + 3; r++)
        {
            for (int c = start_j; c < start_j + 3; c++)
            {
                candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[r][c]), candidates.end());
            }
        }


        static std::mt19937 rng(std::random_device{}());
        std::shuffle(candidates.begin(), candidates.end(), rng);

        for (const int num : candidates)
        {
            sudoku[i][j] = num;
            if (create_sudoku(i, j + 1, probability, sudoku))
            {
                return true;
            }
            sudoku[i][j] = 0;
        }

        return false;
    }

    bool solve_sudoku(int &solutions, const int limit = 2) override
    {
        int row = -1, col = -1;
        bool empty_found = false;

        for (int i = 0; i < 9 && !empty_found; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    row = i; col = j;
                    empty_found = true;
                    break;
                }
            }
        }

        if (!empty_found)
        {
            solutions++;
            return solutions < limit;
        }

        for (int num = 1; num <= 9; num++)
        {
            if (checker.is_valid_sudoku(sudoku, row, col, num))
            {
                sudoku[row][col] = num;
                if (!solve_sudoku(solutions, limit))
                {
                    sudoku[row][col] = 0;
                    return false;
                }
                sudoku[row][col] = 0;
            }
        }

        return true;
    }

    bool has_unique_solution()
    {
        int solutions = 0;
        solve_sudoku(solutions, 2);
        return solutions == 1;
    }

    void deleter(const uint8_t level) override
    {
        static std::mt19937 rng(std::random_device{}());

        std::vector<std::pair<int,int>> cells;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cells.emplace_back(i, j);
            }
        }

        std::shuffle(cells.begin(), cells.end(), rng);

        int to_remove = 20 + level * 5;
        for (auto [i, j] : cells)
        {
            if (to_remove <= 0)
            {
                break;
            }

            const int backup = sudoku[i][j];
            sudoku[i][j] = 0;

            if (!has_unique_solution())
            {
                sudoku[i][j] = backup;
            }
            else
            {
                to_remove--;
            }
        }
    }

    std::array<std::array<int, 9>, 9> generate(const uint8_t level) override
    {
        std::vector<int> probability[9][9]{};

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku[i][j] = 0;
            }
        }

        create_sudoku(0, 0, probability, sudoku);
        deleter(level);

        return sudoku;
    }
};

class sudoku_generator_diagonal final : public sudoku_generator
{
    int sudoku[9][9]{};
public:

};