#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class sudoku_diagonal
{
    char sudoku[9][9]{};
public:
    explicit sudoku_diagonal(char sudoku[9][9])
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
        sudoku[0][3] = '6';
        sudoku[0][4] = '1';
        sudoku[0][5] = '3';

        sudoku[1][4] = '5';

        sudoku[2][0] = '1';
        sudoku[2][4] = '2';
        sudoku[2][8] = '8';

        sudoku[3][1] = '8';
        sudoku[3][2] = '5';
        sudoku[3][6] = '2';
        sudoku[3][7] = '4';

        sudoku[4][2] = '7';
        sudoku[4][6] = '1';

        sudoku[5][1] = '2';
        sudoku[5][2] = '1';
        sudoku[5][6] = '8';
        sudoku[5][7] = '7';

        sudoku[6][0] = '2';
        sudoku[6][4] = '7';
        sudoku[6][8] = '9';

        sudoku[7][4] = '8';

        sudoku[8][3] = '9';
        sudoku[8][4] = '6';
        sudoku[8][5] = '5';
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

                if (i == j)
                {
                    for (int ii = 0; ii < 9; ii++)
                    {
                        if (sudoku[ii][ii] == value && i != ii)
                        {
                            return false;
                        }
                    }
                }

                if (i + j == 8)
                {
                    for (int ii = 0; ii < 9; ii++)
                    {
                        if (sudoku[ii][8 - ii] == value && ii != i)
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

    static void apply_naked_pairs_in_blocks(std::vector<int> what_can_stand[9][9])
    {
        for (int block_i = 0; block_i < 3; block_i++)
        {
            for (int block_j = 0; block_j < 3; block_j++)
            {
                std::vector<std::pair<int, int>> cells_with_two;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        int row = block_i * 3 + i;
                        int col = block_j * 3 + j;

                        if (what_can_stand[row][col].size() == 2)
                        {
                            cells_with_two.emplace_back(row, col);
                        }
                    }
                }

                for (size_t a = 0; a < cells_with_two.size(); a++)
                {
                    for (size_t b = a + 1; b < cells_with_two.size(); b++)
                    {
                        auto [r1, c1] = cells_with_two[a];
                        auto [r2, c2] = cells_with_two[b];

                        if (what_can_stand[r1][c1] == what_can_stand[r2][c2])
                        {
                            const auto& pair = what_can_stand[r1][c1];
                            for (int i = 0; i < 3; i++)
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    const int row = block_i * 3 + i;
                                    const int col = block_j * 3 + j;

                                    if ((row == r1 && col == c1) || (row == r2 && col == c2))
                                    {
                                        continue;
                                    }

                                    for (int val : pair)
                                    {
                                        auto& cell = what_can_stand[row][col];
                                        cell.erase(std::remove(cell.begin(), cell.end(), val), cell.end());
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    static void apply_naked_pairs_in_diagonals(std::vector<int> what_can_stand[9][9])
    {
        // Левая диагональ
        std::vector<std::pair<int, int>> main_diag;
        for (int i = 0; i < 9; i++)
        {
            if (what_can_stand[i][i].size() == 2)
            {
                main_diag.emplace_back(i, i);
            }
        }

        for (size_t a = 0; a < main_diag.size(); a++)
        {
            for (size_t b = a + 1; b < main_diag.size(); b++)
            {
                auto [r1, c1] = main_diag[a];
                auto [r2, c2] = main_diag[b];

                if (what_can_stand[r1][c1] == what_can_stand[r2][c2])
                {
                    const auto& pair = what_can_stand[r1][c1];
                    for (int i = 0; i < 9; i++)
                    {
                        if ((i == r1 && i == c1) || (i == r2 && i == c2))
                        {
                            continue;
                        }

                        for (int val : pair)
                        {
                            auto& cell = what_can_stand[i][i];
                            cell.erase(std::remove(cell.begin(), cell.end(), val), cell.end());
                        }
                    }
                }
            }
        }

        // Правая диагональ
        std::vector<std::pair<int, int>> anti_diag;
        for (int i = 0; i < 9; i++)
        {
            int j = 8 - i;
            if (what_can_stand[i][j].size() == 2)
            {
                anti_diag.emplace_back(i, j);
            }
        }

        for (size_t a = 0; a < anti_diag.size(); a++)
        {
            for (size_t b = a + 1; b < anti_diag.size(); b++)
            {
                auto [r1, c1] = anti_diag[a];
                auto [r2, c2] = anti_diag[b];

                if (what_can_stand[r1][c1] == what_can_stand[r2][c2])
                {
                    const auto& pair = what_can_stand[r1][c1];
                    for (int i = 0; i < 9; i++)
                    {
                        const int j = 8 - i;
                        if ((i == r1 && j == c1) || (i == r2 && j == c2))
                        {
                            continue;
                        }

                        for (int val : pair)
                        {
                            auto& cell = what_can_stand[i][j];
                            cell.erase(std::remove(cell.begin(), cell.end(), val), cell.end());
                        }
                    }
                }
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
                        auto & vec = what_can_stand[i][jj];
                        vec.erase(std::remove(vec.begin(), vec.end(), number), vec.end());

                        if (vec.size() == 1 && sudoku[i][jj] == '-')
                        {
                            sudoku[i][jj] = vec.front() + '0';
                        }
                    }

                    // Проверка стейтов для строки
                    for (int num = 1; num <= 9; num++)
                    {
                        int count = 0;
                        int last_pos = -1;

                        for (int jj = 0; jj < 9; jj++)
                        {
                            auto& vec = what_can_stand[i][jj];

                            if (std::find(vec.begin(), vec.end(), num) != vec.end())
                            {
                                count++;
                                last_pos = jj;
                            }
                        }

                        if (count == 1 && sudoku[i][last_pos] == '-')
                        {
                            sudoku[i][last_pos] = num + '0';
                        }
                    }

                    // Парные значения проверка для строк
                    for (int j1 = 0; j1 < 9; j1++)
                    {
                        if (what_can_stand[i][j1].size() != 2)
                        {
                            continue;
                        }

                        for (int j2 = j1 + 1; j2 < 9; j2++)
                        {
                            if (what_can_stand[i][j2] == what_can_stand[i][j1])
                            {
                                const auto & pair = what_can_stand[i][j1];
                                for (int jj = 0; jj < 9; jj++)
                                {
                                    if (jj == j1 || jj == j2)
                                    {
                                        continue;
                                    }
                                    for (int num : pair)
                                    {
                                        auto & vec = what_can_stand[i][j];
                                        vec.erase(std::remove(vec.begin(), vec.end(), num), vec.end());
                                    }
                                }
                            }
                        }
                    }

                    // Удалить из столбца
                    for (int ii = 0; ii < 9; ii++)
                    {
                        auto & vec = what_can_stand[ii][j];
                        vec.erase(std::remove(vec.begin(), vec.end(), number), vec.end());

                        if (vec.size() == 1 && sudoku[ii][j] == '-')
                        {
                            sudoku[ii][j] = vec.front() + '0';
                        }
                    }

                    // Проверка стейтов для столбца
                    for (int num = 1; num <= 9; num++)
                    {
                        int count = 0;
                        int last_pos = -1;

                        for (int ii = 0; ii < 9; ii++)
                        {
                            auto & vec = what_can_stand[ii][j];

                            if (std::find(vec.begin(), vec.end(), num) != vec.end())
                            {
                                count++;
                                last_pos = ii;
                            }
                        }

                        if (count == 1 && sudoku[last_pos][j] == '-')
                        {
                            sudoku[last_pos][j] = num + '0';
                        }
                    }

                    // Парные значения проверка для столбца
                    for (int i1 = 0; i1 < 9; i1++)
                    {
                        if (what_can_stand[i1][j].size() != 2)
                        {
                            continue;
                        }

                        for (int i2 = i1 + 1; i2 < 9; i2++)
                        {
                            if (what_can_stand[i2][j] == what_can_stand[i1][j])
                            {
                                const auto & pair = what_can_stand[i1][j];
                                for (int ii = 0; ii < 9; ii++)
                                {
                                    if (ii == i1 || ii == i2)
                                    {
                                        continue;
                                    }
                                    for (int num : pair)
                                    {
                                        auto & vec = what_can_stand[i][j];
                                        vec.erase(std::remove(vec.begin(), vec.end(), num), vec.end());
                                    }
                                }
                            }
                        }
                    }

                    // Удалить из квадрата 3x3
                    const int square_i = (i / 3) * 3;
                    const int square_j = (j / 3) * 3;

                    for (int ii = square_i; ii < square_i + 3; ii++)
                    {
                        for (int jj = square_j; jj < square_j + 3; jj++)
                        {
                            auto & vec = what_can_stand[ii][jj];
                            vec.erase(std::remove(vec.begin(), vec.end(), number), vec.end());

                            if (vec.size() == 1 && sudoku[ii][jj] == '-')
                            {
                                sudoku[ii][jj] = vec.front() + '0';
                            }
                        }
                    }

                    // Проверка стейтов для каждого квадрата
                    for (int num = 1; num <= 9; num++)
                    {
                        int count = 0;
                        int last_i = -1, last_j = -1;

                        for (int ii = square_i; ii < square_i + 3; ii++)
                        {
                            for (int jj = square_j; jj < square_j + 3; jj++)
                            {
                                auto& vec = what_can_stand[ii][jj];
                                if (std::find(vec.begin(), vec.end(), num) != vec.end())
                                {
                                    count++;
                                    last_i = ii;
                                    last_j = jj;
                                }
                            }
                        }

                        if (count == 1 && sudoku[last_i][last_j] == '-')
                        {
                            sudoku[last_i][last_j] = num + '0';
                        }
                    }

                    // apply_naked_pairs_in_blocks(what_can_stand);

                    // Удалить из левой диагонали
                    if (i == j)
                    {
                        for (int ii = 0; ii < 9; ii++)
                        {
                            auto & vec = what_can_stand[ii][ii];
                            vec.erase(std::remove(vec.begin(), vec.end(), number), vec.end());

                            if (vec.size() == 1 && sudoku[ii][ii] == '-')
                            {
                                sudoku[ii][ii] = vec.front() + '0';
                            }
                        }
                    }

                    // Проверка стейтов для левой диагонали
                    for (int num = 1; num <= 9; num++)
                    {
                        int count = 0;
                        int last_i = -1;

                        for (int ii = 0; ii < 9; ii++)
                        {
                            auto& vec = what_can_stand[ii][ii];
                            if (std::find(vec.begin(), vec.end(), num) != vec.end())
                            {
                                count++;
                                last_i = ii;
                            }
                        }

                        if (count == 1 && sudoku[last_i][last_i] == '-')
                        {
                            sudoku[last_i][last_i] = num + '0';
                        }
                    }

                    // Удалить из правой диагонали
                    if (i + j == 8)
                    {
                        for (int ii = 0; ii < 9; ii++)
                        {
                            auto & vec = what_can_stand[ii][8 - ii];
                            vec.erase(std::remove(vec.begin(), vec.end(), number), vec.end());

                            if (vec.size() == 1 && sudoku[ii][8 - ii] == '-')
                            {
                                sudoku[ii][8 - ii] = vec.front() + '0';
                            }
                        }
                    }

                    // Проверка стейтов для правой диагонали
                    for (int num = 1; num <= 9; num++)
                    {
                        int count = 0;
                        int last_i = -1;

                        for (int ii = 0; ii < 9; ii++)
                        {
                            int jj = 8 - ii;
                            auto& vec = what_can_stand[ii][jj];
                            if (std::find(vec.begin(), vec.end(), num) != vec.end())
                            {
                                count++;
                                last_i = ii;
                            }
                        }

                        if (count == 1 && sudoku[last_i][8 - last_i] == '-')
                        {
                            sudoku[last_i][8 - last_i] = num + '0';
                        }
                    }

                    // apply_naked_pairs_in_diagonals(what_can_stand);
                }
            }

            iterations++;
            std::cout << "This is " + std::to_string(iterations) + " cycle\n";
            print_sudoku();

            if (check_if_correct())
            {
                std::cout << "Sudoku correct!\n";
            }
        }
    }
};
