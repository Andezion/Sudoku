#pragma once
#include <iostream>

class sudoku_show
{
    int sudoku[9][9]{};
public:
    virtual void show(int sudoku[9][9]) { this.sudoku = sudoku;}

    virtual ~sudoku_show() = default;
};

class sudoku_show_classic final : public sudoku_show
{
    int sudoku[9][9]{};
public:
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
    int sudoku[9][9]{};
public:
    void show() override
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