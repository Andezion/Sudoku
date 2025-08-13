#pragma once
#include <cstdint>
#include <iostream>

class sudoku_generator
{
public:
    virtual void generate(const uint8_t level)
    {

    }
    virtual void show()
    {

    }

    virtual ~sudoku_generator() {}
};

class sudoku_classic final : public sudoku_generator
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