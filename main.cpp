#include "sudoku_generator.h"
#include "sudoku_solver.h"
#include "sudoku_checker.h"
#include "raylib.h"
#include <memory>
#include <array>
#include "sudoku_ui.h"
#include "sudoku_input.h"
#include "sudoku_constants.h"

int main()
{
    InitWindow(screenWidth, screenHeight, "Sudoku Grid (raylib)");
    SetTargetFPS(60);

    int currentGameType = 0;
    std::array<std::array<int, 9>, 9> sudoku9x9{};
    std::array<std::array<int, 16>, 16> sudoku16x16{};
    std::array<std::array<bool, 9>, 9> fixed9x9{};
    std::array<std::array<bool, 16>, 16> fixed16x16{};

    int selectedRow = -1;
    int selectedCol = -1;

    std::unique_ptr<sudoku_checker> checker_ptr;
    HighlightState highlight;

    while (!WindowShouldClose())
    {
        if (const int buttonPressed = buttons_handler(); buttonPressed != 0)
        {
            gameTimer.start();

            currentGameType = buttonPressed;

            if (currentGameType == 1)
            {
                checker_ptr = std::make_unique<sudoku_checker_classic>();
                const sudoku_solver_classic solver(*checker_ptr);

                sudoku_generator_classic generator(*checker_ptr, solver);
                sudoku9x9 = generator.generate9(8);

                for (int r = 0; r < 9; ++r)
                {
                    for (int c = 0; c < 9; ++c)
                    {
                        fixed9x9[r][c] = sudoku9x9[r][c] != 0;
                    }
                }

                highlight.active = false;
            }
            else if (currentGameType == 2)
            {
                checker_ptr = std::make_unique<sudoku_checker_diagonal>();
                const sudoku_solver_diagonal solver(*checker_ptr);

                sudoku_generator_diagonal generator(*checker_ptr, solver);
                sudoku9x9 = generator.generate9(5);

                for (int r = 0; r < 9; ++r)
                {
                    for (int c = 0; c < 9; ++c)
                    {
                        fixed9x9[r][c] = sudoku9x9[r][c] != 0;
                    }
                }

                highlight.active = false;
            }
            else if (currentGameType == 3)
            {
                checker_ptr = std::make_unique<sudoku_checker_big>();
                const sudoku_solver_big solver(*checker_ptr);

                sudoku_generator_big generator(*checker_ptr, solver);
                sudoku16x16 = generator.generate16(5);

                for (int r = 0; r < 16; ++r)
                {
                    for (int c = 0; c < 16; ++c)
                    {
                        fixed16x16[r][c] = sudoku16x16[r][c] != 0;
                    }
                }

                highlight.active = false;
            }
            else
            {
                checker_ptr = std::make_unique<sudoku_checker_samurai>();
                const sudoku_solver_samurai solver(*checker_ptr);

                sudoku_generator_samurai generator(*checker_ptr, solver);
                sudoku16x16 = generator.generate16(5);

                for (int r = 0; r < 16; ++r)
                {
                    for (int c = 0; c < 16; ++c)
                    {
                        fixed16x16[r][c] = sudoku16x16[r][c] != 0;
                    }
                }

                highlight.active = false;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Sudoku grid", 20, 20, 20, DARKGRAY);

        buttons_handler();

        statistic_handlers();

        if (currentGameType == 1)
        {
            handle9x9(sudoku9x9, fixed9x9, checker_ptr, highlight, selectedRow, selectedCol, false, currentGameType);
        }
        else if (currentGameType == 2)
        {
            handle9x9(sudoku9x9, fixed9x9, checker_ptr, highlight, selectedRow, selectedCol, true, currentGameType);
        }
        else if (currentGameType == 3)
        {
            handle16x16(sudoku16x16, fixed16x16, checker_ptr, highlight, selectedRow, selectedCol, currentGameType);
        }

        EndDrawing();
    }

    CloseWindow();

    // int type_sudoku{};
    // std::cout << "Enter type of sudoku: ";
    // std::cin >> type_sudoku;
    //
    // if (type_sudoku == 1)
    // {
    //     const sudoku_checker_diagonal checker;
    //     const sudoku_solver_diagonal solver(checker);
    //     sudoku_generator_diagonal generator(checker, solver);
    //     sudoku_show_diagonal show;
    //
    //     int level{};
    //     std::cout << "Enter level of the sudoku: ";
    //     std::cin >> level;
    //
    //     std::array<std::array<int, 9>, 9> sudoku = generator.generate9(level);
    //
    //     show.show(sudoku);
    //
    //     solver.solve(sudoku);
    //     show.show(sudoku);
    // }
    // else if (type_sudoku == 2)
    // {
    //     const sudoku_checker_classic checker;
    //     const sudoku_solver_classic solver(checker);
    //     sudoku_generator_classic generator(checker, solver);
    //     sudoku_show_classic show;
    //
    //     int level{};
    //     std::cout << "Enter level of the sudoku: ";
    //     std::cin >> level;
    //
    //     std::array<std::array<int, 9>, 9> sudoku = generator.generate9(level);
    //
    //     show.show(sudoku);
    //
    //     solver.solve(sudoku);
    //     show.show(sudoku);
    // }
    // else if (type_sudoku == 3)
    // {
    //     const sudoku_checker_big checker;
    //     const sudoku_solver_big solver(checker);
    //     sudoku_generator_big generator(checker, solver);
    //     sudoku_show_big show;
    //
    //     int level{};
    //     std::cout << "Enter level of the sudoku: ";
    //     std::cin >> level;
    //
    //     std::array<std::array<int, 16>, 16> sudoku = generator.generate16(level);
    //
    //     show.show(sudoku);
    //
    //     solver.solve(sudoku);
    //     show.show(sudoku);
    // }
    // else if (type_sudoku == 4)
    // {
    //     const sudoku_checker_samurai checker;
    //     const sudoku_solver_samurai solver(checker);
    //     sudoku_generator_samurai generator(checker, solver);
    //     sudoku_show_samurai show;
    //
    //     int level{};
    //     std::cout << "Enter level of the sudoku: ";
    //     std::cin >> level;
    //
    //     std::array<std::array<int, 21>, 21> sudoku = generator.generate21(level);
    //
    //     show.show(sudoku);
    //
    //     solver.solve(sudoku);
    //     show.show(sudoku);
    // }
    // else
    // {
    //     std::cerr << "Unknown sudoku type\n";
    //     return 1;
    // }

    return 0;
}