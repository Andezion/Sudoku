// #include "sudoku_classic.h"
// #include "sudoku_diagonal.h"

#include "sudoku_generator.h"
#include "sudoku_show.h"
#include "sudoku_solver.h"


int main()
{
    const sudoku_checker_big classic_checker;
    const sudoku_solver_big solver(classic_checker);
    sudoku_generator_big generator(classic_checker,solver);
    sudoku_show_big show;

    std::array<std::array<int, 16>, 16> sudoku = generator.generate16(7);
    show.show(sudoku);

    solver.solve(sudoku);
    show.show(sudoku);

    return 0;
}
