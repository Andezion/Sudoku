#include <chrono>

// #include "sudoku_classic.h"
// #include "sudoku_diagonal.h"

#include "sudoku_generator.h"
#include "sudoku_show.h"
#include "sudoku_solver.h"


int main()
{
    sudoku_checker_classic classic_checker;
    sudoku_generator_classic generator(classic_checker);
    sudoku_show_classic show;

    std::array<std::array<int, 9>, 9> sudoku = generator.generate(7);
    show.show(sudoku);

    sudoku_solver_classic solver(classic_checker);

    solver.solve(sudoku);
    show.show(sudoku);

    return 0;
}
