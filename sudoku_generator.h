#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>

#include "sudoku_checker.h"
#include "sudoku_solver.h"

class sudoku_generator
{
protected:
    const sudoku_solver & solver;
    const sudoku_checker & checker;
public:
    explicit sudoku_generator(const sudoku_checker& checker, const sudoku_solver& solver)
        : solver(solver), checker(checker) {}

    virtual void symmetrical_diagonal_deleter(uint8_t level) {}
    virtual void symmetrical_horizontal_deleter(uint8_t level) {}
    virtual void symmetrical_vertical_deleter(uint8_t level) {}
    virtual void controlled_deleter() {}
    virtual void figure_deleter() {}
    virtual void deleter(uint8_t level) {}

    virtual std::array<std::array<int, 9>, 9> generate9(const uint8_t level)
    {
        return {};
    }
    virtual std::array<std::array<int, 16>, 16> generate16(const uint8_t level)
    {
        return {};
    }

    virtual ~sudoku_generator() {}
};

class sudoku_generator_classic final : public sudoku_generator
{
    std::array<std::array<int, 9>, 9> sudoku{};
public:
    explicit sudoku_generator_classic(const sudoku_checker& checker, const sudoku_solver& solver)
        : sudoku_generator(checker, solver) {}

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

        std::vector candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};

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

    bool has_unique_solution(std::array<std::array<int, 9>, 9> sudoku) const
    {
        int count = 0;
        count_solutions(sudoku, count, 2);
        return count == 1;
    }

    void count_solutions(std::array<std::array<int, 9>, 9> & sudoku, int &count, const int limit) const
    {
        if (count >= limit)
        {
            return;
        }

        int row = -1, col = -1;
        bool found = false;

        for (int i = 0; i < 9 && !found; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    row = i;
                    col = j;
                    found = true;
                    break;
                }
            }
        }

        if (!found)
        {
            count++;
            return;
        }

        for (int num = 1; num <= 9; num++)
        {
            if (checker.is_valid_sudoku(sudoku, row, col, num))
            {
                sudoku[row][col] = num;
                count_solutions(sudoku, count, limit);
                sudoku[row][col] = 0;
            }
        }
    }

    void controlled_deleter() override
    {
        static std::mt19937 rng(std::random_device{}());

        std::vector<std::pair<int,int>> cells;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cells.emplace_back(i, j);
            }
        }

        std::shuffle(cells.begin(), cells.end(), rng);

        int to_remove = 20;
        for (auto [i, j] : cells)
        {
            if (to_remove <= 0)
            {
                break;
            }

            const int backup = sudoku[i][j];
            const int backup_two = sudoku[8 - i][j];
            const int backup_three = sudoku[i][8 - j];
            const int backup_four = sudoku[8 - i][8 - j];


            sudoku[i][j] = 0;
            sudoku[8 - i][j] = 0;
            sudoku[i][8 - j] = 0;
            sudoku[8 - i][8 - j] = 0;

            if (!has_unique_solution(sudoku))
            {
                sudoku[i][j] = backup;
                sudoku[8 - i][j] = backup_two;
                sudoku[i][8 - j] = backup_three;
                sudoku[8 - i][8 - j] = backup_four;
            }
            else
            {
                to_remove -= 4;
            }
        }
    }

    void symmetrical_diagonal_deleter(const uint8_t level) override
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

        int to_remove = 20 + 5 * level;
        for (auto [i, j] : cells)
        {
            if (to_remove <= 0)
            {
                break;
            }

            const int backup_one = sudoku[i][j];
            const int backup_two = sudoku[8 - i][8 - j];
            sudoku[i][j] = 0;
            sudoku[8 - i][8 - j] = 0;

            if (!has_unique_solution(sudoku))
            {
                sudoku[i][j] = backup_one;
                sudoku[8 - i][8 - j] = backup_two;
            }
            else
            {
                to_remove -= 2;
            }
        }
    }

    void symmetrical_vertical_deleter(const uint8_t level) override
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

            const int backup_one = sudoku[i][j];
            const int backup_two = sudoku[i][8 - j];
            sudoku[i][j] = 0;
            sudoku[i][8 - j] = 0;

            if (!has_unique_solution(sudoku))
            {
                sudoku[i][j] = backup_one;
                sudoku[i][8 - j] = backup_two;
            }
            else
            {
                to_remove -= 2;
            }
        }
    }

    void symmetrical_horizontal_deleter(const uint8_t level) override
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

            const int backup_one = sudoku[i][j];
            const int backup_two = sudoku[8 - i][j];
            sudoku[i][j] = 0;
            sudoku[8 - i][j] = 0;

            if (!has_unique_solution(sudoku))
            {
                sudoku[i][j] = backup_one;
                sudoku[8 - i][j] = backup_two;
            }
            else
            {
                to_remove -= 2;
            }
        }
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

            if (!has_unique_solution(sudoku))
            {
                sudoku[i][j] = backup;
            }
            else
            {
                to_remove--;
            }
        }
    }

    std::array<std::array<int, 9>, 9> generate9(const uint8_t level) override
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
        //symmetrical_horizontal_deleter();
        //symmetrical_vertical_deleter(level);
        controlled_deleter();
        //symmetrical_diagonal_deleter();

        //deleter(level);

        return sudoku;
    }
};

class sudoku_generator_diagonal final : public sudoku_generator
{
    std::array<std::array<int, 9>, 9> sudoku{};
public:
    explicit sudoku_generator_diagonal(const sudoku_checker& checker, const sudoku_solver& solver)
        : sudoku_generator(checker, solver) {}

    static bool create_sudoku(int i, int j, std::array<std::array<int, 9>, 9> & sudoku)
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
            return create_sudoku(i, j + 1, sudoku);
        }

        std::vector candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        for (int col = 0; col < 9; col++)
        {
            candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[i][col]), candidates.end());
        }

        for (int row = 0; row < 9; row++)
        {
            candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[row][j]), candidates.end());
        }

        if (i == j)
        {
            for (int d = 0; d < 9; d++)
            {
                candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[d][d]), candidates.end());
            }
        }
        if (i + j == 8)
        {
            for (int d = 0; d < 9; d++)
            {
                candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[d][8 - d]), candidates.end());
            }
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
            if (create_sudoku(i, j + 1, sudoku))
            {
                return true;
            }
            sudoku[i][j] = 0;
        }

        return false;
    }

    bool has_unique_solution(std::array<std::array<int, 9>, 9> sudoku) const
    {
        int count = 0;
        count_solutions(sudoku, count, 2);
        return count == 1;
    }

    void count_solutions(std::array<std::array<int, 9>, 9> & sudoku, int &count, const int limit) const
    {
        if (count >= limit)
        {
            return;
        }

        int row = -1, col = -1;
        bool found = false;

        for (int i = 0; i < 9 && !found; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    row = i;
                    col = j;
                    found = true;
                    break;
                }
            }
        }

        if (!found)
        {
            count++;
            return;
        }

        for (int num = 1; num <= 9; num++)
        {
            if (checker.is_valid_sudoku(sudoku, row, col, num))
            {
                sudoku[row][col] = num;
                count_solutions(sudoku, count, limit);
                sudoku[row][col] = 0;
            }
        }
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

            if (!has_unique_solution(sudoku))
            {
                sudoku[i][j] = backup;
            }
            else
            {
                to_remove--;
            }
        }
    }

    std::array<std::array<int, 9>, 9> generate9(const uint8_t level) override
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku[i][j] = 0;
            }
        }

        create_sudoku(0, 0, sudoku);
        deleter(level);

        return sudoku;
    }
};

class sudoku_generator_big final : public sudoku_generator
{
    std::array<std::array<int, 16>, 16> sudoku{};
public:
    explicit sudoku_generator_big(const sudoku_checker& checker, const sudoku_solver& solver)
        : sudoku_generator(checker, solver) {}

    static bool create_sudoku(int i, int j, std::vector<int> probability[16][16], std::array<std::array<int, 16>, 16> & sudoku)
    {
        if (j == 16)
        {
            j = 0;
            i++;
        }
        if (i == 16)
        {
            return true;
        }

        if (sudoku[i][j] != 0)
        {
            return create_sudoku(i, j + 1, probability, sudoku);
        }

        std::vector candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

        for (int col = 0; col < 16; col++)
        {
            candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[i][col]), candidates.end());
        }

        for (int row = 0; row < 16; row++)
        {
            candidates.erase(std::remove(candidates.begin(), candidates.end(), sudoku[row][j]), candidates.end());
        }

        const int start_i = i / 4 * 4;
        const int start_j = j / 4 * 4;
        for (int r = start_i; r < start_i + 4; r++)
        {
            for (int c = start_j; c < start_j + 4; c++)
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

    bool has_unique_solution(std::array<std::array<int, 16>, 16> sudoku) const
    {
        int count = 0;
        count_solutions(sudoku, count, 2);
        return count == 1;
    }

    void count_solutions(std::array<std::array<int, 16>, 16> & sudoku, int &count, const int limit) const
    {
        if (count >= limit)
        {
            return;
        }

        int row = -1, col = -1;
        bool found = false;

        for (int i = 0; i < 16 && !found; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    row = i;
                    col = j;
                    found = true;
                    break;
                }
            }
        }

        if (!found)
        {
            count++;
            return;
        }

        for (int num = 1; num <= 16; num++)
        {
            if (checker.is_valid_sudoku(sudoku, row, col, num))
            {
                sudoku[row][col] = num;
                count_solutions(sudoku, count, limit);
                sudoku[row][col] = 0;
            }
        }
    }

    void deleter(const uint8_t level) override
    {
        static std::mt19937 rng(std::random_device{}());

        std::vector<std::pair<int,int>> cells;
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
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

            if (!has_unique_solution(sudoku))
            {
                sudoku[i][j] = backup;
            }
            else
            {
                to_remove--;
            }
        }
    }

    std::array<std::array<int, 16>, 16> generate16(const uint8_t level) override
    {
        std::vector<int> probability[16][16]{};

        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                sudoku[i][j] = 0;
            }
        }

        create_sudoku(0, 0, probability, sudoku);
        deleter(level);

        return sudoku;
    }
};