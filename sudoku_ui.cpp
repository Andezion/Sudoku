#include "sudoku_ui.h"
#include <string>

std::string valueToStr(int v)
{
    if (v >= 1 && v <= 9) return std::to_string(v);
    if (v >= 10 && v <= 15) return std::string(1, 'A' + (v - 10));
    return std::string();
}
