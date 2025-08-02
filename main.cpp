#include "sudoku_classic.h"
#include "sudoku_diagonal.h"

int main()
{
    char sudoku[9][9]{};
    // sudoku_classic sudoku_classic(sudoku);
    //
    // sudoku_classic.create_sudoku();
    // sudoku_classic.init_sudoku();
    // sudoku_classic.print_sudoku();
    // sudoku_classic.sudoku_solver();



    sudoku_diagonal sudoku_diagonal(sudoku);
    sudoku_diagonal.create_sudoku();
    sudoku_diagonal.init_sudoku();
    sudoku_diagonal.print_sudoku();
    sudoku_diagonal.sudoku_solver();

    return 0;
}
