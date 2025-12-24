#include "sudoku_ui.h"

GameTimer gameTimer;
int counter = 0;
int last_remaining_steps{};
int last_solver_steps{};
double last_solver_time_ms{};

std::string valueToStr(const int v)
{
    if (v >= 1 && v <= 9)
    {
        return std::to_string(v);
    }
    if (v >= 10 && v <= 15)
    {
        return std::string(1, 'A' + (v - 10));
    }
    return std::string();
}

int buttons_handler()
{
    constexpr Rectangle button_classic = { 800, 100, 150, 50 };
    const Vector2 mouse_classic = GetMousePosition();
    const bool hover_classic = CheckCollisionPointRec(mouse_classic, button_classic);
    const Color color_classic = hover_classic ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(button_classic, color_classic);
    DrawText("Classic", button_classic.x + 36, button_classic.y + 15, 20, DARKGRAY);

    constexpr Rectangle button_diagonal = { 800, 200, 150, 50 };
    const Vector2 mouse_diagonal = GetMousePosition();
    const bool hover_diagonal = CheckCollisionPointRec(mouse_diagonal, button_diagonal);
    const Color color_diagonal = hover_diagonal ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(button_diagonal, color_diagonal);
    DrawText("Diagonal", button_diagonal.x + 31, button_diagonal.y + 15, 20, DARKGRAY);

    constexpr Rectangle button_big = { 800, 300, 150, 50 };
    const Vector2 mouse_big = GetMousePosition();
    const bool hover_big = CheckCollisionPointRec(mouse_big, button_big);
    const Color color_big = hover_big ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(button_big, color_big);
    DrawText("Big", button_big.x + 57, button_big.y + 15, 20, DARKGRAY);

    constexpr Rectangle button_samurai = { 800, 400, 150, 50 };
    const Vector2 mouse_samurai = GetMousePosition();
    const bool hover_samurai = CheckCollisionPointRec(mouse_samurai, button_samurai);
    const Color color_samurai = hover_samurai ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(button_samurai, color_samurai);
    DrawText("Samurai", button_samurai.x + 34, button_samurai.y + 15, 20, DARKGRAY);

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

void statistic_handlers()
{
    constexpr Rectangle font = { 800, 500, 150, 210 };
    DrawRectangleRec(font, LIGHTGRAY);
    DrawText("Statistics", font.x + 23, font.y + 15, 20, DARKGRAY);

    if (gameTimer.isRunning)
    {
        int hours, minutes, seconds;
        gameTimer.getTimeFormatted(hours, minutes, seconds);

        const char* timeText = TextFormat("Time: %02d:%02d:%02d", hours, minutes, seconds);
        //std::cout << timeText << std::endl;
        DrawText(timeText, font.x + 10, font.y + 50, 20, DARKGRAY);
    }
    else
    {
        DrawText("Time: --:--:--", font.x + 10, font.y + 50, 20, GRAY);
    }

    if (counter == 0)
    {
        DrawText(("Counter: " + std::to_string(counter)).c_str(), font.x + 10, font.y + 80, 20, GRAY);
    }
    else
    {
        DrawText(("Counter: " + std::to_string(counter)).c_str(), font.x + 10, font.y + 80, 20, DARKGRAY);
    }

    if (last_remaining_steps == 0)
    {
        DrawText(("Left: " + std::to_string(last_remaining_steps)).c_str(), font.x + 10, font.y + 110, 20, GRAY);
    }
    else
    {
        DrawText(("Left: " + std::to_string(last_remaining_steps)).c_str(), font.x + 10, font.y + 110, 20, DARKGRAY);
    }

    if (last_solver_steps == 0)
    {
        DrawText(TextFormat("Steps: %d", last_solver_steps), font.x + 10, font.y + 140, 20, GRAY);
    }
    else
    {
        DrawText(TextFormat("Steps: %d", last_solver_steps), font.x + 10, font.y + 140, 20, DARKGRAY);
    }

    if (last_solver_time_ms <= 0.0)
    {
        DrawText("Time: - ms", font.x + 10, font.y + 170, 20, GRAY);
    }
    else
    {
        DrawText(TextFormat("Time: %.0f mks", last_solver_time_ms / 1000.0), font.x + 10, font.y + 170, 20, DARKGRAY);
    }
}
