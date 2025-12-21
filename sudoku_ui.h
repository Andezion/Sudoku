#pragma once
#include <string>
#include "raylib.h"
#include <iostream>

struct GameTimer
{
    double startTime = 0.0;
    double pausedTime = 0.0;
    bool isRunning = false;
    bool isPaused = false;

    void start()
    {
        startTime = GetTime();
        pausedTime = 0.0;
        isRunning = true;
        isPaused = false;
    }

    void reset()
    {
        startTime = 0.0;
        pausedTime = 0.0;
        isRunning = false;
        isPaused = false;
    }

    double getElapsed() const
    {
        if (!isRunning)
        {
            return 0.0;
        }
        return GetTime() - startTime - pausedTime;
    }

    void getTimeFormatted(int& hours, int& minutes, int& seconds) const
    {
        const int totalSeconds = static_cast<int>(getElapsed());
        hours = totalSeconds / 3600;
        minutes = totalSeconds % 3600 / 60;
        seconds = totalSeconds % 60;
    }
};

static GameTimer gameTimer;

std::string valueToStr(int v);
int buttons_handler();
void statistic_handlers();
int check_button_press();
void draw_buttons();