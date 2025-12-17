#pragma once

// Shared UI/layout constants
inline constexpr int screenWidth = 1000;
inline constexpr int screenHeight = 800;

inline constexpr int gridSize_default = 9;
inline constexpr int cellSize = 60;
inline constexpr int gridPixelSize = gridSize_default * cellSize;

inline constexpr int offsetX = (screenWidth - 200 - gridPixelSize) / 2;
inline constexpr int offsetY = (screenHeight - gridPixelSize) / 2;

inline constexpr int gridSize_big = 16;
inline constexpr int cellSize_big = 37;
inline constexpr int gridPixelSize_big = gridSize_big * cellSize_big;

inline constexpr int offsetX_big = (screenWidth - 200 - gridPixelSize_big) / 2;
inline constexpr int offsetY_big = (screenHeight - gridPixelSize_big) / 2;
