#pragma once
#include <iostream>

class sudoku_show
{
public:
    virtual void show(const std::array<std::array<int, 9>, 9> & sudoku) {}
    virtual void show(const std::array<std::array<int, 16>, 16> & sudoku) {}

    virtual ~sudoku_show() = default;
};

class sudoku_show_classic final : public sudoku_show
{
public:
    void show(const std::array<std::array<int, 9>, 9> & sudoku) override
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
                    std::cout << "_" << "  ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "=========================" << std::endl;
    }
};

class sudoku_show_diagonal final : public sudoku_show
{
public:
    void show(const std::array<std::array<int, 9>, 9> & sudoku) override
    {
        std::cout << "==== SUDOKU DIAGONAL ====" << std::endl;
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
                    std::cout << "_" << "  ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "=========================" << std::endl;
    }
};

class sudoku_show_big final : public sudoku_show
{
public:
    void show(const std::array<std::array<int, 16>, 16> & sudoku) override
    {
        std::cout << "======= SUDOKU  BIG =======" << std::endl;
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                if (sudoku[i][j] != 0)
                {
                    std::cout << sudoku[i][j] << "  ";
                }
                else
                {
                    std::cout << "_" << "  ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "===============================" << std::endl;
    }
};