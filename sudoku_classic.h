#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class sudoku_classic
{
    char sudoku[9][9]{};
public:
    explicit sudoku_classic(char sudoku[9][9])
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                this->sudoku[i][j] = sudoku[i][j];
            }
        }
    }

    void print_sudoku() const
    {
        std::cout << std::endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                std::cout << sudoku[i][j] << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void init_sudoku()
    {
        sudoku[0][1] = '8';
        sudoku[0][7] = '1';

        sudoku[1][0] = '7';
        sudoku[1][1] = '3';
        sudoku[1][3] = '8';
        sudoku[1][5] = '6';
        sudoku[1][7] = '9';
        sudoku[1][8] = '4';

        sudoku[2][3] = '1';
        sudoku[2][5] = '9';

        sudoku[3][2] = '3';
        sudoku[3][4] = '7';
        sudoku[3][6] = '8';

        sudoku[4][3] = '6';
        sudoku[4][5] = '3';

        sudoku[5][2] = '6';
        sudoku[5][4] = '8';
        sudoku[5][6] = '5';

        sudoku[6][3] = '2';
        sudoku[6][5] = '5';

        sudoku[7][0] = '6';
        sudoku[7][1] = '4';
        sudoku[7][3] = '9';
        sudoku[7][5] = '8';
        sudoku[7][7] = '7';
        sudoku[7][8] = '5';

        sudoku[8][1] = '9';
        sudoku[8][7] = '4';
    }

    bool check_if_correct() const
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                const char value = sudoku[i][j];
                if (value == '-')
                {
                    return false;
                }

                // Проверка строки
                for (int k = 0; k < 9; k++)
                {
                    if (k != j && sudoku[i][k] == value)
                    {
                        return false;
                    }
                }

                // Проверка столбца
                for (int l = 0; l < 9; l++)
                {
                    if (l != i && sudoku[l][j] == value)
                    {
                        return false;
                    }
                }

                // Проверка квадрата 3x3
                const int square_i = (i / 3) * 3;
                const int square_j = (j / 3) * 3;

                for (int ii = square_i; ii < square_i + 3; ii++)
                {
                    for (int jj = square_j; jj < square_j + 3; jj++)
                    {
                        if ((ii != i || jj != j) && sudoku[ii][jj] == value)
                        {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    void create_sudoku()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                sudoku[i][j] = '-';
            }
        }
    }

    void sudoku_solver()
    {
        std::vector<int> what_can_stand[9][9];
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                what_can_stand[i][j] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            }
        }

        int iterations = 0;

        while (!check_if_correct())
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (sudoku[i][j] == '-')
                    {
                        continue;
                    }

                    int number = sudoku[i][j] - '0';

                    // Удалить из строки
                    for (int jj = 0; jj < 9; jj++)
                    {
                        auto& vec = what_can_stand[i][jj];
                        vec.erase(std::remove(vec.begin(), vec.end(), number), vec.end());

                        if (vec.size() == 1 && sudoku[i][jj] == '-')
                        {
                            sudoku[i][jj] = vec.front() + '0';
                        }
                    }

                    // Удалить из столбца
                    for (int ii = 0; ii < 9; ii++)
                    {
                        auto& vec = what_can_stand[ii][j];
                        vec.erase(std::remove(vec.begin(), vec.end(), number), vec.end());

                        if (vec.size() == 1 && sudoku[ii][j] == '-')
                        {
                            sudoku[ii][j] = vec.front() + '0';
                        }
                    }

                    // Удалить из квадрата 3x3
                    const int square_i = (i / 3) * 3;
                    const int square_j = (j / 3) * 3;

                    for (int ii = square_i; ii < square_i + 3; ii++)
                    {
                        for (int jj = square_j; jj < square_j + 3; jj++)
                        {
                            auto& vec = what_can_stand[ii][jj];
                            vec.erase(std::remove(vec.begin(), vec.end(), number), vec.end());

                            if (vec.size() == 1 && sudoku[ii][jj] == '-')
                            {
                                sudoku[ii][jj] = vec.front() + '0';
                            }
                        }
                    }
                }
            }

            iterations++;
            std::cout << "This is " + std::to_string(iterations) + " cycle\n";
            print_sudoku();
        }
    }
};
