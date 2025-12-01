#include "sudoku_generator.h"
#include "sudoku_show.h"
#include "sudoku_solver.h"
#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes");

    float rotation = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        rotation += 0.2f;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("some basic shapes available on raylib", 20, 20, 20, DARKGRAY);

            DrawCircle(screenWidth/5, 120, 35, DARKBLUE);
            DrawCircleGradient(screenWidth/5, 220, 60, GREEN, SKYBLUE);
            DrawCircleLines(screenWidth/5, 340, 80, DARKBLUE);
            DrawEllipse(screenWidth/5, 120, 25, 20, YELLOW);
            DrawEllipseLines(screenWidth/5, 120, 30, 25, YELLOW);

            DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, RED);
            DrawRectangleGradientH(screenWidth/4*2 - 90, 170, 180, 130, MAROON, GOLD);
            DrawRectangleLines(screenWidth/4*2 - 40, 320, 80, 60, ORANGE);  // NOTE: Uses QUADS internally, not lines

            DrawTriangle((Vector2){ screenWidth/4.0f *3.0f, 80.0f },
                         (Vector2){ screenWidth/4.0f *3.0f - 60.0f, 150.0f },
                         (Vector2){ screenWidth/4.0f *3.0f + 60.0f, 150.0f }, VIOLET);

            DrawTriangleLines((Vector2){ screenWidth/4.0f*3.0f, 160.0f },
                              (Vector2){ screenWidth/4.0f*3.0f - 20.0f, 230.0f },
                              (Vector2){ screenWidth/4.0f*3.0f + 20.0f, 230.0f }, DARKBLUE);

            DrawPoly((Vector2){ screenWidth/4.0f*3, 330 }, 6, 80, rotation, BROWN);
            DrawPolyLines((Vector2){ screenWidth/4.0f*3, 330 }, 6, 90, rotation, BROWN);
            DrawPolyLinesEx((Vector2){ screenWidth/4.0f*3, 330 }, 6, 85, rotation, 6, BEIGE);

            DrawLine(18, 42, screenWidth - 18, 42, BLACK);
        EndDrawing();
    }

    CloseWindow();

    int type_sudoku{};
    std::cout << "Enter type of sudoku: ";
    std::cin >> type_sudoku;

    if (type_sudoku == 1)
    {
        const sudoku_checker_diagonal checker;
        const sudoku_solver_diagonal solver(checker);
        sudoku_generator_diagonal generator(checker, solver);
        sudoku_show_diagonal show;

        int level{};
        std::cout << "Enter level of the sudoku: ";
        std::cin >> level;

        std::array<std::array<int, 9>, 9> sudoku = generator.generate9(level);

        show.show(sudoku);

        solver.solve(sudoku);
        show.show(sudoku);
    }
    else if (type_sudoku == 2)
    {
        const sudoku_checker_classic checker;
        const sudoku_solver_classic solver(checker);
        sudoku_generator_classic generator(checker, solver);
        sudoku_show_classic show;

        int level{};
        std::cout << "Enter level of the sudoku: ";
        std::cin >> level;

        std::array<std::array<int, 9>, 9> sudoku = generator.generate9(level);

        show.show(sudoku);

        solver.solve(sudoku);
        show.show(sudoku);
    }
    else if (type_sudoku == 3)
    {
        const sudoku_checker_big checker;
        const sudoku_solver_big solver(checker);
        sudoku_generator_big generator(checker, solver);
        sudoku_show_big show;

        int level{};
        std::cout << "Enter level of the sudoku: ";
        std::cin >> level;

        std::array<std::array<int, 16>, 16> sudoku = generator.generate16(level);

        show.show(sudoku);

        solver.solve(sudoku);
        show.show(sudoku);
    }
    else if (type_sudoku == 4)
    {
        const sudoku_checker_samurai checker;
        const sudoku_solver_samurai solver(checker);
        sudoku_generator_samurai generator(checker, solver);
        sudoku_show_samurai show;

        int level{};
        std::cout << "Enter level of the sudoku: ";
        std::cin >> level;

        std::array<std::array<int, 21>, 21> sudoku = generator.generate21(level);

        show.show(sudoku);

        solver.solve(sudoku);
        show.show(sudoku);
    }
    else
    {
        std::cerr << "Unknown sudoku type\n";
        return 1;
    }


    return 0;
}
