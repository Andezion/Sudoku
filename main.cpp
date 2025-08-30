// #include "sudoku_classic.h"
// #include "sudoku_diagonal.h"

#include "sudoku_generator.h"
#include "sudoku_show.h"
#include "sudoku_solver.h"


int main()
{
    const sudoku_checker_diagonal classic_checker;
    const sudoku_solver_diagonal solver(classic_checker);
    sudoku_show_diagonal show;

    std::array<std::array<int, 9>, 9> solution = {{
        {{0, 0, 5, 1, 0, 4, 9, 0, 0}},
        {{0, 0, 0, 8, 0, 3, 0, 0, 0}},
        {{0, 0, 3, 0, 2, 0, 8, 0, 0}},
        {{3, 0, 0, 0, 0, 0, 0, 0, 9}},
        {{0, 0, 4, 0, 0, 0, 2, 0, 0}},
        {{1, 0, 0, 0, 0, 0, 0, 0, 8}},
        {{0, 0, 6, 0, 9, 0, 5, 0, 0}},
        {{0, 0, 0, 6, 0, 1, 0, 0, 0}},
        {{0, 0, 9, 5, 0, 2, 6, 0, 0}}
    }};

    show.show(solution);

    solver.solve(solution);
    show.show(solution);

    return 0;
}
