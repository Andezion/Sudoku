#pragma once

class sudoku_checker
{
public:
    virtual bool is_valid_sudoku(const std::array<std::array<int, 9>, 9> & sudoku,
        const int row, const int col, const int num) const
    {
        return false;
    }
    virtual bool is_valid_sudoku(const std::array<std::array<int, 16>, 16> & sudoku,
        const int row, const int col, const int num) const
    {
        return false;
    }
    virtual bool is_valid_sudoku(const std::array<std::array<int, 21>, 21> & sudoku,
        const int row, const int col, const int num) const
    {
        return false;
    }

    virtual ~sudoku_checker() = default;
};

class sudoku_checker_classic final : public sudoku_checker
{
public:
    bool is_valid_sudoku(const std::array<std::array<int, 9>, 9> & sudoku,
        const int row, const int col, const int num) const override
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
public:
    bool is_valid_sudoku(const std::array<std::array<int, 9>, 9>& sudoku,
                         const int row, const int col, const int num) const override
    {
        for (int x = 0; x < 9; x++)
        {
            if (sudoku[row][x] == num || sudoku[x][col] == num)
            {
                return false;
            }

            if (sudoku[row - row % 3 + x / 3][col - col % 3 + x % 3] == num)
            {
                return false;
            }
        }

        if (row == col)
        {
            for (int i = 0; i < 9; i++)
            {
                if (sudoku[i][i] == num)
                {
                    return false;
                }
            }
        }

        if (row + col == 8)
        {
            for (int i = 0; i < 9; i++)
            {
                if (sudoku[i][8 - i] == num)
                {
                    return false;
                }
            }
        }

        return true;
    }
};

class sudoku_checker_big final : public sudoku_checker
{
public:
    bool is_valid_sudoku(const std::array<std::array<int, 16>, 16> & sudoku,
        const int row, const int col, const int num) const override
    {
        for (int x = 0; x < 16; x++)
        {
            if (sudoku[row][x] == num)
            {
                return false;
            }
            if (sudoku[x][col] == num)
            {
                return false;
            }
            if (sudoku[row - row % 4 + x / 4][col - col % 4 + x % 4] == num)
            {
                return false;
            }
        }
        return true;
    }
};

class sudoku_checker_samurai final : public sudoku_checker
{
public:
    bool is_valid_sudoku(const std::array<std::array<int, 21>, 21> & sudoku,
                         const int row, const int col, const int num) const override
    {
        int r0 = -1, c0 = -1;
        if (row >= 0 && row <= 8 && col >= 0 && col <= 8)
        {
            r0 = 0, c0 = 0;
        }
        else if (row >= 0 && row <= 8 && col >= 12 && col <= 20)
        {
            r0 = 0, c0 = 12;
        }
        else if (row >= 6 && row <= 14 && col >= 6 && col <= 14)
        {
            r0 = 6, c0 = 6;
        }
        else if (row >= 12 && row <= 20 && col >= 0 && col <= 8)
        {
            r0 = 12, c0 = 0;
        }
        else if (row >= 12 && row <= 20 && col >= 12 && col <= 20)
        {
            r0 = 12, c0 = 12;
        }
        else
        {
            return true;
        }

        for (int i = 0; i < 9; i++)
        {
            if (sudoku[row][c0 + i] == num)
            {
                return false;
            }

            if (sudoku[r0 + i][col] == num)
            {
                return false;
            }
        }

        const int br = r0 + (row - r0) / 3 * 3;
        const int bc = c0 + (col - c0) / 3 * 3;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (sudoku[br + i][bc + j] == num)
                {
                    return false;
                }
            }
        }

        return true;
    }
};