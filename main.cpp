// #include "sudoku_classic.h"
// #include "sudoku_diagonal.h"

#include "sudoku_generator.h"
#include "sudoku_show.h"
#include "sudoku_solver.h"


int main()
{
    const sudoku_checker_diagonal classic_checker;
    const sudoku_solver_diagonal solver(classic_checker);
    sudoku_generator_diagonal generator(classic_checker, solver);
    sudoku_show_diagonal show;

    std::array<std::array<int, 9>, 9> sudoku = generator.generate9(7);

    show.show(sudoku);

    solver.solve(sudoku);
    show.show(sudoku);

    return 0;
}
