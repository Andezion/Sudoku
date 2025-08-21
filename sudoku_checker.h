#pragma once
#include <iostream>

class sudoku_checker
{
public:
    virtual void show() {}

    virtual ~sudoku_checker() = default;
};

class sudoku_checker_classic final : public sudoku_checker
{
    int sudoku[9][9]{};
public:

};

class sudoku_checker_diagonal final : public sudoku_checker
{
    int sudoku[9][9]{};
public:

};