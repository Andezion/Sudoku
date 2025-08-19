#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <random>

class sudoku_generator
{
public:
    virtual void deleter(uint8_t level) {}
    virtual void generate(const uint8_t level) {}
    virtual void show() {}

    virtual ~sudoku_generator() {}
};

class sudoku_classic final : public sudoku_generator
{
    int sudoku[9][9]{};
public:
    static bool fillCell(int i, int j, std::vector<int> probability[9][9], int sudoku[9][9])
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
            return fillCell(i, j + 1, probability, sudoku);
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

        std::random_shuffle(candidates.begin(), candidates.end());

        for (const int num : candidates)
        {
            sudoku[i][j] = num;
            if (fillCell(i, j + 1, probability, sudoku))
            {
                return true;
            }
            sudoku[i][j] = 0;
        }

        return false;
    }

    void deleter(uint8_t level) override
    {
        std::random_device dev;
        std::mt19937 rng(dev());

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10 - level);
                if (dist6(rng) == 1)
                {
                    sudoku[i][j] = 0;
                }
            }
        }

    }

    void generate(const uint8_t level) override
    {
        std::vector<int> probability[9][9]{};

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku[i][j] = 0;
            }
        }

        fillCell(0, 0, probability, sudoku);
        deleter(level);
    }
    void show() override
    {
        std::cout << "==== SUDOKU  CLASSIC ====" << std::endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (sudoku[i][j] != 0)
                {
                    std::cout << sudoku[i][j] << "  ";
                }
                else
                {
                    std::cout << " " << "  ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "=========================" << std::endl;
    }
};

class sudoku_diagonal final : public sudoku_generator
{
    int sudoku[9][9]{};
public:
    void generate(const uint8_t level) override
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku[i][j] = i + j;
            }
        }
    }
    void show() override
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                std::cout << sudoku[i][j] % 9 << "  ";
            }
            std::cout << std::endl;
        }
    }
};