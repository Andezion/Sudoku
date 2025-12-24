#include "sudoku_input.h"
#include "sudoku_ui.h"
#include "raylib.h"
#include "sudoku_constants.h"
#include <string>

void handle9x9(std::array<std::array<int,9>,9>& board,
               const std::array<std::array<bool,9>,9>& fixed9x9,
               const std::unique_ptr<sudoku_checker>& checker_ptr,
               HighlightState& highlight,
               int& selectedRow,
               int& selectedCol,
               const bool diagonalMode,
               int& currentGameType)
{
    const auto [x, y] = GetMousePosition();
    int hoverRow = -1;
    int hoverCol = -1;

    if (x >= offsetX && x < offsetX + gridPixelSize &&
        y >= offsetY && y < offsetY + gridPixelSize)
    {
        hoverCol = static_cast<int>((x - offsetX) / cellSize);
        hoverRow = static_cast<int>((y - offsetY) / cellSize);

        const Rectangle hoverRec = {
            static_cast<float>(offsetX + hoverCol * cellSize),
            static_cast<float>(offsetY + hoverRow * cellSize),
            static_cast<float>(cellSize),
            static_cast<float>(cellSize)
        };

        DrawRectangleRec(hoverRec, Fade(SKYBLUE, 0.25f));
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverRow != -1 && hoverCol != -1)
    {
        selectedRow = hoverRow;
        selectedCol = hoverCol;
    }

    if (selectedRow != -1 && selectedCol != -1)
    {
        const Rectangle selRec = {
            static_cast<float>(offsetX + selectedCol * cellSize),
            static_cast<float>(offsetY + selectedRow * cellSize),
            static_cast<float>(cellSize),
            static_cast<float>(cellSize)
        };
        DrawRectangleRec(selRec, Fade(GREEN, 0.25f));

        auto try_place = [&](const int value)
        {
            if (fixed9x9[selectedRow][selectedCol])
            {
                highlight.active = true;
                highlight.expiresAt = GetTime() + 1.0;
                highlight.selRow = selectedRow;
                highlight.selCol = selectedCol;
                highlight.conflictRow = -1;
                highlight.conflictCol = -1;
                return;
            }
            auto boardCopy = board;

            boardCopy[selectedRow][selectedCol] = 0;
            if (checker_ptr)
            {
                if (checker_ptr->is_valid_sudoku(boardCopy, selectedRow, selectedCol, value))
                {
                    board[selectedRow][selectedCol] = value;
                    highlight.active = false;
                }
                else
                {
                    int cr = -1, cc = -1;
                    for (int c = 0; c < 9; ++c)
                    {
                        if (board[selectedRow][c] == value)
                        {
                            cr = selectedRow; cc = c;
                            break;
                        }
                    }
                    if (cr == -1)
                    {
                        for (int r = 0; r < 9; ++r)
                        {
                            if (board[r][selectedCol] == value)
                            {
                                cr = r; cc = selectedCol;
                                break;
                            }
                        }
                    }
                    if (cr == -1)
                    {
                        const int br = selectedRow - selectedRow % 3;
                        const int bc = selectedCol - selectedCol % 3;

                        for (int i = 0; i < 3; ++i)
                        {
                            for (int j = 0; j < 3; ++j)
                            {
                                if (board[br + i][bc + j] == value)
                                {
                                    cr = br + i; cc = bc + j; break;
                                }
                            }
                        }
                    }

                    if (cr == -1 && diagonalMode)
                    {
                        int diagType = 0;
                        if (selectedRow == selectedCol)
                        {
                            for (int i = 0; i < 9; ++i)
                            {
                                if (board[i][i] == value)
                                {
                                    diagType = 1;
                                    break;
                                }
                            }
                        }
                        if (diagType == 0 && selectedRow + selectedCol == 8)
                        {
                            for (int i = 0; i < 9; ++i)
                            {
                                if (board[i][8 - i] == value)
                                {
                                    diagType = 2;
                                    break;
                                }
                            }
                        }

                        if (diagType != 0)
                        {
                            highlight.active = true;
                            highlight.expiresAt = GetTime() + 2.0;
                            highlight.selRow = selectedRow;
                            highlight.selCol = selectedCol;
                            highlight.conflictRow = -1;
                            highlight.conflictCol = -1;
                            highlight.diagonalType = diagType;
                            highlight.conflictValue = value;
                            return;
                        }
                    }

                    highlight.active = true;
                    highlight.expiresAt = GetTime() + 2.0;
                    highlight.selRow = selectedRow;
                    highlight.selCol = selectedCol;
                    highlight.conflictRow = cr;
                    highlight.conflictCol = cc;
                    highlight.diagonalType = 0;
                    highlight.conflictValue = 0;
                }
            }
            else
            {
                board[selectedRow][selectedCol] = value;
                highlight.active = false;
            }
        };

        if (IsKeyPressed(KEY_ONE)) try_place(1);
        if (IsKeyPressed(KEY_TWO)) try_place(2);
        if (IsKeyPressed(KEY_THREE)) try_place(3);
        if (IsKeyPressed(KEY_FOUR)) try_place(4);
        if (IsKeyPressed(KEY_FIVE)) try_place(5);
        if (IsKeyPressed(KEY_SIX)) try_place(6);
        if (IsKeyPressed(KEY_SEVEN)) try_place(7);
        if (IsKeyPressed(KEY_EIGHT)) try_place(8);
        if (IsKeyPressed(KEY_NINE)) try_place(9);

    }

    if (highlight.active)
    {
        if (GetTime() > highlight.expiresAt)
        {
            highlight.active = false;
            highlight.diagonalType = 0;
            highlight.conflictValue = 0;
            highlight.conflictRow = -1;
            highlight.conflictCol = -1;
        }
        else
        {
            if (highlight.diagonalType != 0)
            {
                for (int i = 0; i < 9; ++i)
                {
                    const int r = highlight.diagonalType == 1 ? i : i;
                    const int c = highlight.diagonalType == 1 ? i : 8 - i;

                    const Rectangle drec = {
                        static_cast<float>(offsetX + c * cellSize),
                        static_cast<float>(offsetY + r * cellSize),
                        static_cast<float>(cellSize),
                        static_cast<float>(cellSize)
                    };
                    DrawRectangleRec(drec, Fade(ORANGE, 0.35f));

                    if (highlight.conflictValue != 0 && board[r][c] == highlight.conflictValue)
                    {
                        const Rectangle confH = {
                            static_cast<float>(offsetX + c * cellSize),
                            static_cast<float>(offsetY + r * cellSize),
                            static_cast<float>(cellSize),
                            static_cast<float>(cellSize)
                        };
                        DrawRectangleRec(confH, Fade(RED, 0.6f));
                    }
                }
            }
            else
            {
                for (int c = 0; c < 9; ++c)
                {
                    const Rectangle r = {
                        static_cast<float>(offsetX + c * cellSize),
                        static_cast<float>(offsetY + highlight.selRow * cellSize),
                        static_cast<float>(cellSize),
                        static_cast<float>(cellSize)
                    };
                    DrawRectangleRec(r, Fade(ORANGE, 0.35f));
                }
                for (int r = 0; r < 9; ++r)
                {
                    const Rectangle rrec = {
                        static_cast<float>(offsetX + highlight.selCol * cellSize),
                        static_cast<float>(offsetY + r * cellSize),
                        static_cast<float>(cellSize),
                        static_cast<float>(cellSize)
                    };
                    DrawRectangleRec(rrec, Fade(ORANGE, 0.35f));
                }

                if (highlight.conflictRow != -1 && highlight.conflictCol != -1)
                {
                    const Rectangle confH = {
                        static_cast<float>(offsetX + highlight.conflictCol * cellSize),
                        static_cast<float>(offsetY + highlight.conflictRow * cellSize),
                        static_cast<float>(cellSize),
                        static_cast<float>(cellSize)
                    };
                    DrawRectangleRec(confH, Fade(RED, 0.6f));
                }
            }
        }
    }

    for (int i = 0; i <= gridSize_default; i++)
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
            if (const int value = board[row][col]; value != 0)
            {
                const int posX = offsetX + col * cellSize + cellSize / 2 - 10;
                const int posY = offsetY + row * cellSize + cellSize / 2 - 10;

                DrawText(TextFormat("%d", value), posX, posY, 30, BLACK);
            }
        }
    }

    static bool celebrate = false;
    static double celebrateEnd = 0.0;

    auto is_solved9 = [&]() -> bool {
        if (!checker_ptr) return false;
        for (int r = 0; r < 9; ++r)
        {
            for (int c = 0; c < 9; ++c)
            {
                const int v = board[r][c];
                if (v == 0) return false;
                auto copy = board;
                copy[r][c] = 0;
                if (!checker_ptr->is_valid_sudoku(copy, r, c, v)) return false;
            }
        }
        return true;
    };

    if (!celebrate && is_solved9())
    {
        celebrate = true;
        celebrateEnd = GetTime() + 1.0;
        gameTimer.reset();
        ++counter;
    }

    if (celebrate)
    {
        const float alpha = GetTime() < celebrateEnd ? 0.95f : 0.95f;
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(GOLD, alpha));

        constexpr Rectangle againBtn = { static_cast<float>(screenWidth/2 - 75), static_cast<float>(screenHeight/2 - 25), 150.0f, 50.0f };
        const Vector2 mp = GetMousePosition();
        const bool hover = CheckCollisionPointRec(mp, againBtn);
        DrawRectangleRec(againBtn, hover ? SKYBLUE : LIGHTGRAY);
        DrawText("Again?!", static_cast<int>(againBtn.x + 25), static_cast<int>(againBtn.y + 12), 30, DARKGRAY);

        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            celebrate = false;
          
            currentGameType = 0;
        }

        if (GetTime() > celebrateEnd)
        {
           
        }
    }
}

void handleSamurai(std::array<std::array<int,21>,21>& board,
                   const std::array<std::array<bool,21>,21>& fixed,
                   const std::unique_ptr<sudoku_checker>& checker_ptr,
                   HighlightState& highlight,
                   int& selectedRow,
                   int& selectedCol,
                   int& currentGameType)
{
    const auto [x, y] = GetMousePosition();

    auto cellExists = [&](const int r, const int c) -> bool
    {
        if (r >= 0 && r <= 8 && c >= 0 && c <= 8)
        {
            return true;
        }
        if (r >= 0 && r <= 8 && c >= 12 && c <= 20)
        {
            return true;
        }
        if (r >= 6 && r <= 14 && c >= 6 && c <= 14)
        {
            return true;
        }
        if (r >= 12 && r <= 20 && c >= 0 && c <= 8)
        {
            return true;
        }
        if (r >= 12 && r <= 20 && c >= 12 && c <= 20)
        {
            return true;
        }
        return false;
    };

    int hoverRow = -1;
    int hoverCol = -1;

    if (x >= offsetX_samurai && x < offsetX_samurai + gridPixelSize_samurai &&
        y >= offsetY_samurai && y < offsetY_samurai + gridPixelSize_samurai)
    {
        const int c = static_cast<int>((x - offsetX_samurai) / cellSize_samurai);

        if (const int r = static_cast<int>((y - offsetY_samurai) / cellSize_samurai);
            r >= 0 && r < 21 && c >= 0 && c < 21 && cellExists(r, c))
        {
            hoverRow = r;
            hoverCol = c;
            const Rectangle hoverRec = {
                static_cast<float>(offsetX_samurai + hoverCol * cellSize_samurai),
                static_cast<float>(offsetY_samurai + hoverRow * cellSize_samurai),
                static_cast<float>(cellSize_samurai),
                static_cast<float>(cellSize_samurai)
            };
            DrawRectangleRec(hoverRec, Fade(SKYBLUE, 0.25f));
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverRow != -1 && hoverCol != -1)
    {
        selectedRow = hoverRow;
        selectedCol = hoverCol;
    }

    if (selectedRow != -1 && selectedCol != -1 && cellExists(selectedRow, selectedCol))
    {
        const Rectangle selRec = {
            static_cast<float>(offsetX_samurai + selectedCol * cellSize_samurai),
            static_cast<float>(offsetY_samurai + selectedRow * cellSize_samurai),
            static_cast<float>(cellSize_samurai),
            static_cast<float>(cellSize_samurai)
        };
        DrawRectangleRec(selRec, Fade(GREEN, 0.25f));

        auto try_place = [&](const int value)
        {
            if (fixed[selectedRow][selectedCol])
            {
                highlight.active = true;
                highlight.expiresAt = GetTime() + 1.0;
                highlight.selRow = selectedRow;
                highlight.selCol = selectedCol;
                highlight.conflictRow = -1;
                highlight.conflictCol = -1;
                return;
            }

            auto boardCopy = board;
            boardCopy[selectedRow][selectedCol] = 0;

            if (checker_ptr)
            {
                if (checker_ptr->is_valid_sudoku(boardCopy, selectedRow, selectedCol, value))
                {
                    board[selectedRow][selectedCol] = value;
                    highlight.active = false;
                }
                else
                {
                    int cr = -1, cc = -1;

                    int r0 = 0, c0 = 0;
                    if (selectedRow >= 0 && selectedRow <= 8 && selectedCol >= 0 && selectedCol <= 8)
                    {
                        r0 = 0;
                        c0 = 0;
                    }
                    else if (selectedRow >= 0 && selectedRow <= 8 && selectedCol >= 12 && selectedCol <= 20)
                    {
                        r0 = 0;
                        c0 = 12;
                    }
                    else if (selectedRow >= 6 && selectedRow <= 14 && selectedCol >= 6 && selectedCol <= 14)
                    {
                        r0 = 6;
                        c0 = 6;
                    }
                    else if (selectedRow >= 12 && selectedRow <= 20 && selectedCol >= 0 && selectedCol <= 8)
                    {
                        r0 = 12;
                        c0 = 0;
                    }
                    else if (selectedRow >= 12 && selectedRow <= 20 && selectedCol >= 12 && selectedCol <= 20)
                    {
                        r0 = 12;
                        c0 = 12;
                    }

                    for (int c = 0; c < 9; ++c)
                    {
                        if (board[selectedRow][c0 + c] == value)
                        {
                            cr = selectedRow; cc = c0 + c;
                            break;
                        }
                    }

                    if (cr == -1)
                    {
                        for (int r = 0; r < 9; ++r)
                        {
                            if (board[r0 + r][selectedCol] == value)
                            {
                                cr = r0 + r; cc = selectedCol;
                                break;
                            }
                        }
                    }

                    if (cr == -1)
                    {
                        const int br = r0 + (selectedRow - r0) / 3 * 3;
                        const int bc = c0 + (selectedCol - c0) / 3 * 3;
                        for (int i = 0; i < 3; ++i)
                        {
                            for (int j = 0; j < 3; ++j)
                            {
                                if (board[br + i][bc + j] == value)
                                {
                                    cr = br + i; cc = bc + j;
                                    break;
                                }
                            }
                        }
                    }

                    highlight.active = true;
                    highlight.expiresAt = GetTime() + 2.0;
                    highlight.selRow = selectedRow;
                    highlight.selCol = selectedCol;
                    highlight.conflictRow = cr;
                    highlight.conflictCol = cc;
                    highlight.diagonalType = 0;
                    highlight.conflictValue = 0;
                }
            }
            else
            {
                board[selectedRow][selectedCol] = value;
                highlight.active = false;
            }
        };

        if (IsKeyPressed(KEY_ONE)) try_place(1);
        if (IsKeyPressed(KEY_TWO)) try_place(2);
        if (IsKeyPressed(KEY_THREE)) try_place(3);
        if (IsKeyPressed(KEY_FOUR)) try_place(4);
        if (IsKeyPressed(KEY_FIVE)) try_place(5);
        if (IsKeyPressed(KEY_SIX)) try_place(6);
        if (IsKeyPressed(KEY_SEVEN)) try_place(7);
        if (IsKeyPressed(KEY_EIGHT)) try_place(8);
        if (IsKeyPressed(KEY_NINE)) try_place(9);
    }

    if (highlight.active)
    {
        if (GetTime() > highlight.expiresAt)
        {
            highlight.active = false;
            highlight.conflictRow = -1;
            highlight.conflictCol = -1;
            highlight.diagonalType = 0;
            highlight.conflictValue = 0;
        }
        else
        {
            if (highlight.conflictRow != -1 && highlight.conflictCol != -1)
            {
                for (int c = 0; c < 21; ++c)
                {
                    if (!cellExists(highlight.selRow, c)) continue;
                    const Rectangle r = {
                        static_cast<float>(offsetX_samurai + c * cellSize_samurai),
                        static_cast<float>(offsetY_samurai + highlight.selRow * cellSize_samurai),
                        static_cast<float>(cellSize_samurai),
                        static_cast<float>(cellSize_samurai)
                    };
                    DrawRectangleRec(r, Fade(ORANGE, 0.35f));
                }
                for (int r = 0; r < 21; ++r)
                {
                    if (!cellExists(r, highlight.selCol))
                    {
                        continue;
                    }

                    const Rectangle rrec = {
                        static_cast<float>(offsetX_samurai + highlight.selCol * cellSize_samurai),
                        static_cast<float>(offsetY_samurai + r * cellSize_samurai),
                        static_cast<float>(cellSize_samurai),
                        static_cast<float>(cellSize_samurai)
                    };
                    DrawRectangleRec(rrec, Fade(ORANGE, 0.35f));
                }

                const Rectangle confH = {
                    static_cast<float>(offsetX_samurai + highlight.conflictCol * cellSize_samurai),
                    static_cast<float>(offsetY_samurai + highlight.conflictRow * cellSize_samurai),
                    static_cast<float>(cellSize_samurai),
                    static_cast<float>(cellSize_samurai)
                };
                DrawRectangleRec(confH, Fade(RED, 0.6f));
            }
        }
    }

    for (int r = 0; r < 21; ++r)
    {
        for (int c = 0; c < 21; ++c)
        {
            if (!cellExists(r, c))
            {
                continue;
            }

            const Rectangle crect = {
                static_cast<float>(offsetX_samurai + c * cellSize_samurai),
                static_cast<float>(offsetY_samurai + r * cellSize_samurai),
                static_cast<float>(cellSize_samurai),
                static_cast<float>(cellSize_samurai)
            };

            DrawRectangleLinesEx(crect, 1.0f, BLACK);
            if (const int v = board[r][c]; v != 0)
            {
                const int posX = offsetX_samurai + c * cellSize_samurai + cellSize_samurai / 2 - 8;
                const int posY = offsetY_samurai + r * cellSize_samurai + cellSize_samurai / 2 - 10;

                DrawText(TextFormat("%d", v), posX, posY, 20, BLACK);
            }
        }
    }

    const std::array<std::pair<int,int>,5> blocks = {{{0,0},{0,12},{6,6},{12,0},{12,12}}};
    for (const auto &[fst, snd] : blocks)
    {
        const int r0 = fst;
        const int c0 = snd;

        for (int i = 0; i <= 9; ++i)
        {
            const int thickness = i % 3 == 0 ? 3 : 1;

            const float y1 = static_cast<float>(offsetY_samurai + (r0 + i) * cellSize_samurai);
            DrawLineEx({static_cast<float>(offsetX_samurai + c0 * cellSize_samurai), y1},
                {static_cast<float>(offsetX_samurai + (c0+9) * cellSize_samurai), y1}, thickness, BLACK);

            const float x1 = static_cast<float>(offsetX_samurai + (c0 + i) * cellSize_samurai);
            DrawLineEx({x1, static_cast<float>(offsetY_samurai + r0 * cellSize_samurai)},
                {x1, static_cast<float>(offsetY_samurai + (r0+9) * cellSize_samurai)}, thickness, BLACK);
        }
    }

    static bool celebrate = false;
    static double celebrateEnd = 0.0;

    auto is_solved_samurai = [&]() -> bool
    {
        if (!checker_ptr)
        {
            return false;
        }

        for (int r = 0; r < 21; ++r)
        {
            for (int c = 0; c < 21; ++c)
            {
                if (!cellExists(r, c))
                {
                    continue;
                }

                const int v = board[r][c];

                if (v == 0)
                {
                    return false;
                }

                auto copy = board;
                copy[r][c] = 0;
                if (!checker_ptr->is_valid_sudoku(copy, r, c, v)) return false;
            }
        }
        return true;
    };

    if (!celebrate && is_solved_samurai())
    {
        celebrate = true;
        celebrateEnd = GetTime() + 1.0;
        gameTimer.reset();
        ++counter;
    }

    if (celebrate)
    {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(GOLD, 0.95f));

        constexpr Rectangle againBtn = { static_cast<float>(screenWidth/2 - 75), static_cast<float>(screenHeight/2 - 25), 150.0f, 50.0f };
        const Vector2 mp = GetMousePosition();
        const bool hover = CheckCollisionPointRec(mp, againBtn);

        DrawRectangleRec(againBtn, hover ? SKYBLUE : LIGHTGRAY);

        DrawText("Again?!", static_cast<int>(againBtn.x + 25), static_cast<int>(againBtn.y + 12), 30, DARKGRAY);

        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            celebrate = false;
            currentGameType = 0;
        }
    }
}

void handle16x16(std::array<std::array<int,16>,16>& board,
                 const std::array<std::array<bool,16>,16>& fixed,
                 const std::unique_ptr<sudoku_checker>& checker_ptr,
                 HighlightState& highlight,
                 int& selectedRow,
                 int& selectedCol,
                 int& currentGameType)
{
    const auto [x, y] = GetMousePosition();

    int hoverRow = -1;
    int hoverCol = -1;

    if (x >= offsetX_big && x < offsetX_big + gridPixelSize_big &&
        y >= offsetY_big && y < offsetY_big + gridPixelSize_big)
    {
        hoverCol = static_cast<int>((x - offsetX_big) / cellSize_big);
        hoverRow = static_cast<int>((y - offsetY_big) / cellSize_big);

        const Rectangle hoverRec = {
            static_cast<float>(offsetX_big + hoverCol * cellSize_big),
            static_cast<float>(offsetY_big + hoverRow * cellSize_big),
            static_cast<float>(cellSize_big),
            static_cast<float>(cellSize_big)
        };
        DrawRectangleRec(hoverRec, Fade(SKYBLUE, 0.25f));
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverRow != -1 && hoverCol != -1)
    {
        selectedRow = hoverRow;
        selectedCol = hoverCol;
    }

    if (selectedRow != -1 && selectedCol != -1)
    {
        const Rectangle selRec = {
            static_cast<float>(offsetX_big + selectedCol * cellSize_big),
            static_cast<float>(offsetY_big + selectedRow * cellSize_big),
            static_cast<float>(cellSize_big),
            static_cast<float>(cellSize_big)
        };
        DrawRectangleRec(selRec, Fade(GREEN, 0.25f));

        auto try_place = [&](const int value)
        {
            if (fixed[selectedRow][selectedCol])
            {
                highlight.active = true;
                highlight.expiresAt = GetTime() + 1.0;
                highlight.selRow = selectedRow;
                highlight.selCol = selectedCol;
                highlight.conflictRow = -1;
                highlight.conflictCol = -1;
                return;
            }
            auto boardCopy = board;

            boardCopy[selectedRow][selectedCol] = 0;
            if (checker_ptr)
            {
                if (checker_ptr->is_valid_sudoku(boardCopy, selectedRow, selectedCol, value))
                {
                    board[selectedRow][selectedCol] = value;
                    highlight.active = false;
                }
                else
                {
                    int cr = -1, cc = -1;
                    for (int c = 0; c < 16; ++c)
                    {
                        if (board[selectedRow][c] == value)
                        {
                            cr = selectedRow;
                            cc = c;

                            break;
                        }
                    }
                    if (cr == -1)
                    {
                        for (int r = 0; r < 16; ++r)
                        {
                            if (board[r][selectedCol] == value)
                            {
                                cr = r;
                                cc = selectedCol;

                                break;
                            }
                        }
                    }
                    if (cr == -1)
                    {
                        const int br = selectedRow - selectedRow % 4;
                        const int bc = selectedCol - selectedCol % 4;
                        for (int i = 0; i < 4; ++i)
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                if (board[br + i][bc + j] == value)
                                {
                                    cr = br + i; cc = bc + j; break;
                                }
                            }
                        }
                    }

                    if (cr == -1)
                    {
                        int diagType = 0;
                        if (selectedRow == selectedCol)
                        {
                            for (int i = 0; i < 16; ++i)
                            {
                                if (board[i][i] == value)
                                {
                                    diagType = 1;
                                    break;
                                }
                            }
                        }
                        if (diagType == 0 && selectedRow + selectedCol == 15)
                        {
                            for (int i = 0; i < 16; ++i)
                            {
                                if (board[i][15 - i] == value)
                                {
                                    diagType = 2;
                                    break;
                                }
                            }
                        }

                        if (diagType != 0)
                        {
                            highlight.active = true;
                            highlight.expiresAt = GetTime() + 2.0;
                            highlight.selRow = selectedRow;
                            highlight.selCol = selectedCol;
                            highlight.conflictRow = -1;
                            highlight.conflictCol = -1;
                            highlight.diagonalType = diagType;
                            highlight.conflictValue = value;
                            return;
                        }
                    }

                    highlight.active = true;
                    highlight.expiresAt = GetTime() + 2.0;
                    highlight.selRow = selectedRow;
                    highlight.selCol = selectedCol;
                    highlight.conflictRow = cr;
                    highlight.conflictCol = cc;
                    highlight.diagonalType = 0;
                    highlight.conflictValue = 0;
                }
            }
            else
            {
                board[selectedRow][selectedCol] = value;
                highlight.active = false;
            }
        };

        if (IsKeyPressed(KEY_ONE)) try_place(1);
        if (IsKeyPressed(KEY_TWO)) try_place(2);
        if (IsKeyPressed(KEY_THREE)) try_place(3);
        if (IsKeyPressed(KEY_FOUR)) try_place(4);
        if (IsKeyPressed(KEY_FIVE)) try_place(5);
        if (IsKeyPressed(KEY_SIX)) try_place(6);
        if (IsKeyPressed(KEY_SEVEN)) try_place(7);
        if (IsKeyPressed(KEY_EIGHT)) try_place(8);
        if (IsKeyPressed(KEY_NINE)) try_place(9);
        if (IsKeyPressed(KEY_A)) try_place(10);
        if (IsKeyPressed(KEY_B)) try_place(11);
        if (IsKeyPressed(KEY_C)) try_place(12);
        if (IsKeyPressed(KEY_D)) try_place(13);
        if (IsKeyPressed(KEY_E)) try_place(14);
        if (IsKeyPressed(KEY_F)) try_place(15);
    }

    if (highlight.active)
    {
        if (GetTime() > highlight.expiresAt)
        {
            highlight.active = false;
        }
        else
        {
            for (int c = 0; c < 16; ++c)
            {
                const Rectangle r = {
                    static_cast<float>(offsetX_big + c * cellSize_big),
                    static_cast<float>(offsetY_big + highlight.selRow * cellSize_big),
                    static_cast<float>(cellSize_big),
                    static_cast<float>(cellSize_big)
                };
                DrawRectangleRec(r, Fade(ORANGE, 0.35f));
            }
            for (int r = 0; r < 16; ++r)
            {
                const Rectangle rrec = {
                    static_cast<float>(offsetX_big + highlight.selCol * cellSize_big),
                    static_cast<float>(offsetY_big + r * cellSize_big),
                    static_cast<float>(cellSize_big),
                    static_cast<float>(cellSize_big)
                };
                DrawRectangleRec(rrec, Fade(ORANGE, 0.35f));
            }

            if (highlight.conflictRow != -1 && highlight.conflictCol != -1)
            {
                const Rectangle confH = {
                    static_cast<float>(offsetX_big + highlight.conflictCol * cellSize_big),
                    static_cast<float>(offsetY_big + highlight.conflictRow * cellSize_big),
                    static_cast<float>(cellSize_big),
                    static_cast<float>(cellSize_big)
                };
                DrawRectangleRec(confH, Fade(RED, 0.6f));
            }
        }
    }

    for (int i = 0; i <= gridSize_big; i++)
    {
        constexpr int blockSize = 4;
        const int thickness = i % blockSize != 0 ? 1 : 4;

        DrawLineEx(
            {static_cast<float>(offsetX_big), static_cast<float>(offsetY_big + i * cellSize_big)},
            {static_cast<float>(offsetX_big + gridPixelSize_big), static_cast<float>(offsetY_big + i * cellSize_big)},
            thickness,
            BLACK
        );

        DrawLineEx(
            {static_cast<float>(offsetX_big + i * cellSize_big), static_cast<float>(offsetY_big)},
            {static_cast<float>(offsetX_big + i * cellSize_big), static_cast<float>(offsetY_big + gridPixelSize_big)},
            thickness,
            BLACK
        );
    }

    for (int row = 0; row < 16; row++)
    {
        for (int col = 0; col < 16; col++)
        {
            if (const int value = board[row][col]; value != 0)
            {
                const int posX = offsetX_big + col * cellSize_big + cellSize_big / 2 - 10;
                const int posY = offsetY_big + row * cellSize_big + cellSize_big / 2 - 10;

                const std::string s = valueToStr(value);

                DrawText(s.c_str(), posX, posY, 20, BLACK);
            }
        }
    }

    static bool celebrate16 = false;
    static double celebrate16End = 0.0;

    auto is_solved16 = [&]() -> bool
    {
        if (!checker_ptr)
        {
            return false;
        }
        for (int r = 0; r < 16; ++r)
        {
            for (int c = 0; c < 16; ++c)
            {
                const int v = board[r][c];
                if (v == 0)
                {
                    return false;
                }

                auto copy = board;
                copy[r][c] = 0;
                if (!checker_ptr->is_valid_sudoku(copy, r, c, v))
                {
                    return false;
                }
            }
        }
        return true;
    };

    if (!celebrate16 && is_solved16())
    {
        celebrate16 = true;
        celebrate16End = GetTime() + 1.0;
        gameTimer.reset();
        ++counter;
    }

    if (celebrate16)
    {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(GOLD, 0.95f));

        const Rectangle againBtn = { static_cast<float>(screenWidth/2 - 75), static_cast<float>(screenHeight/2 - 25), 150.0f, 50.0f };
        const Vector2 mp = GetMousePosition();
        const bool hover = CheckCollisionPointRec(mp, againBtn);
        DrawRectangleRec(againBtn, hover ? SKYBLUE : LIGHTGRAY);
        DrawText("Again?!", static_cast<int>(againBtn.x + 25), static_cast<int>(againBtn.y + 12), 30, DARKGRAY);

        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            celebrate16 = false;
            currentGameType = 0;
        }
    }
}
