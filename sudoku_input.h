#pragma once
#include <array>
#include <memory>
#include "sudoku_checker.h"

struct HighlightState
{
    bool active = false;
    double expiresAt = 0.0;
    int selRow = -1;
    int selCol = -1;
    int conflictRow = -1;
    int conflictCol = -1;
    int diagonalType = 0;
    int conflictValue = 0;
};

void handle9x9(std::array<std::array<int,9>,9>& board,
               const std::array<std::array<bool,9>,9>& fixed,
               const std::unique_ptr<sudoku_checker>& checker_ptr,
               HighlightState& highlight,
               int& selectedRow,
               int& selectedCol,
               bool diagonalMode);

void handle16x16(std::array<std::array<int,16>,16>& board,
                 const std::array<std::array<bool,16>,16>& fixed,
                 const std::unique_ptr<sudoku_checker>& checker_ptr,
                 HighlightState& highlight,
                 int& selectedRow,
                 int& selectedCol);
