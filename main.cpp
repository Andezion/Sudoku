#include "sudoku_generator.h"
#include "sudoku_solver.h"
#include "raylib.h"

constexpr int screenWidth = 1000;
constexpr int screenHeight = 800;

constexpr int gridSize = 9;
constexpr int cellSize = 60;
constexpr int gridPixelSize = gridSize * cellSize;

constexpr int offsetX = (screenWidth - 200 - gridPixelSize) / 2;
constexpr int offsetY = (screenHeight - gridPixelSize) / 2;

int buttons_handler()
{
    constexpr Rectangle button_classic = { 800, 100, 150, 50 };
    const Vector2 mouse_classic = GetMousePosition();
    const bool hover_classic = CheckCollisionPointRec(mouse_classic, button_classic);
    const Color color_classic = hover_classic ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(button_classic, color_classic);
    DrawText("Classic", button_classic.x + 20, button_classic.y + 15, 20, DARKGRAY);

    constexpr Rectangle button_diagonal = { 800, 200, 150, 50 };
    const Vector2 mouse_diagonal = GetMousePosition();
    const bool hover_diagonal = CheckCollisionPointRec(mouse_diagonal, button_diagonal);
    const Color color_diagonal = hover_diagonal ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(button_diagonal, color_diagonal);
    DrawText("Diagonal", button_diagonal.x + 20, button_diagonal.y + 15, 20, DARKGRAY);

    constexpr Rectangle button_big = { 800, 300, 150, 50 };
    const Vector2 mouse_big = GetMousePosition();
    const bool hover_big = CheckCollisionPointRec(mouse_big, button_big);
    const Color color_big = hover_big ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(button_big, color_big);
    DrawText("Big", button_big.x + 20, button_big.y + 15, 20, DARKGRAY);

    constexpr Rectangle button_samurai = { 800, 400, 150, 50 };
    const Vector2 mouse_samurai = GetMousePosition();
    const bool hover_samurai = CheckCollisionPointRec(mouse_samurai, button_samurai);
    const Color color_samurai = hover_samurai ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(button_samurai, color_samurai);
    DrawText("Samurai", button_samurai.x + 20, button_samurai.y + 15, 20, DARKGRAY);

    if (hover_classic && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return 1;
    }
    if (hover_diagonal && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return 2;
    }
    if (hover_big && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return 3;
    }
    if (hover_samurai && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return 4;
    }

    return 0;
}

int main()
{
    InitWindow(screenWidth, screenHeight, "Sudoku Grid (raylib)");
    SetTargetFPS(60);

    int currentGameType = 0;
    std::array<std::array<int, 9>, 9> sudoku9x9{};

    while (!WindowShouldClose())
    {
        if (const int buttonPressed = buttons_handler(); buttonPressed != 0)
        {
            currentGameType = buttonPressed;

            if (currentGameType == 1)
            {
                const sudoku_checker_classic checker;
                const sudoku_solver_classic solver(checker);
                sudoku_generator_classic generator(checker, solver);
                sudoku9x9 = generator.generate9(8);
            }
            else if (currentGameType == 2)
            {
                const sudoku_checker_diagonal checker;
                const sudoku_solver_diagonal solver(checker);
                sudoku_generator_diagonal generator(checker, solver);
                sudoku9x9 = generator.generate9(5);
            }
            else if (currentGameType == 3)
            {
                const sudoku_checker_big checker;
                const sudoku_solver_big solver(checker);
                sudoku_generator_big generator(checker, solver);
                sudoku9x9 = generator.generate9(5);
            }
            else
            {
                const sudoku_checker_samurai checker;
                const sudoku_solver_samurai solver(checker);
                sudoku_generator_samurai generator(checker, solver);
                sudoku9x9 = generator.generate9(5);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Sudoku grid", 20, 20, 20, DARKGRAY);

        if (currentGameType == 1)
        {
            for (int i = 0; i <= gridSize; i++)
            {
                constexpr int blockSize = 3;
                const int thickness = i % blockSize != 0 ? 1 : 4;

                DrawLineEx(
                    {static_cast<float>(offsetX), static_cast<float>(offsetY + i * cellSize)},
                    {static_cast<float>(offsetX + gridPixelSize), static_cast<float>(offsetY + i * cellSize)},
                    thickness,
                    BLACK
                );

                DrawLineEx(
                    {static_cast<float>(offsetX + i * cellSize), static_cast<float>(offsetY)},
                    {static_cast<float>(offsetX + i * cellSize), static_cast<float>(offsetY + gridPixelSize)},
                    thickness,
                    BLACK
                );
            }

            for (int row = 0; row < 9; row++)
            {
                for (int col = 0; col < 9; col++)
                {
                    if (const int value = sudoku9x9[row][col]; value != 0)
                    {
                        const int posX = offsetX + col * cellSize + cellSize / 2 - 10;
                        const int posY = offsetY + row * cellSize + cellSize / 2 - 10;

                        DrawText(TextFormat("%d", value), posX, posY, 30, BLACK);
                    }
                }
            }
        }
        else if (currentGameType == 2)
        {
            DrawLineEx(
                {static_cast<float>(offsetX), static_cast<float>(offsetY)},
                {static_cast<float>(offsetX + gridSize * cellSize), static_cast<float>(offsetY + gridSize * cellSize)},
                1,
                BLACK
            );
            DrawLineEx(
                {static_cast<float>(offsetX + gridSize * cellSize), static_cast<float>(offsetY)},
                {static_cast<float>(offsetX), static_cast<float>(offsetY + gridSize * cellSize)},
                1,
                BLACK
            );

            for (int i = 0; i <= gridSize; i++)
            {
                constexpr int blockSize = 3;
                const int thickness = i % blockSize != 0 ? 1 : 4;

                DrawLineEx(
                    {static_cast<float>(offsetX), static_cast<float>(offsetY + i * cellSize)},
                    {static_cast<float>(offsetX + gridPixelSize), static_cast<float>(offsetY + i * cellSize)},
                    thickness,
                    BLACK
                );

                DrawLineEx(
                    {static_cast<float>(offsetX + i * cellSize), static_cast<float>(offsetY)},
                    {static_cast<float>(offsetX + i * cellSize), static_cast<float>(offsetY + gridPixelSize)},
                    thickness,
                    BLACK
                );
            }

            for (int row = 0; row < 9; row++)
            {
                for (int col = 0; col < 9; col++)
                {
                    if (const int value = sudoku9x9[row][col]; value != 0)
                    {
                        const int posX = offsetX + col * cellSize + cellSize / 2 - 10;
                        const int posY = offsetY + row * cellSize + cellSize / 2 - 10;

                        DrawText(TextFormat("%d", value), posX, posY, 30, BLACK);
                    }
                }
            }
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
