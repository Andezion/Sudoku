#include "sudoku_generator.h"
#include "sudoku_show.h"
#include "sudoku_solver.h"


int main()
{
    int type_sudoku{};
    std::cout << "Enter type of sudoku: ";
    std::cin >> type_sudoku;

    if (type_sudoku == 1)
    {
        const sudoku_checker_diagonal checker;
        const sudoku_solver_diagonal solver(checker);
        sudoku_generator_diagonal generator(checker, solver);
        sudoku_show_diagonal show;

        int level{};
        std::cout << "Enter level of the sudoku: ";
        std::cin >> level;

        std::array<std::array<int, 9>, 9> sudoku = generator.generate9(level);

        show.show(sudoku);

        solver.solve(sudoku);
        show.show(sudoku);
    }
    else if (type_sudoku == 2)
    {
        const sudoku_checker_classic checker;
        const sudoku_solver_classic solver(checker);
        sudoku_generator_classic generator(checker, solver);
        sudoku_show_classic show;

        int level{};
        std::cout << "Enter level of the sudoku: ";
        std::cin >> level;

        std::array<std::array<int, 9>, 9> sudoku = generator.generate9(level);

        show.show(sudoku);

        solver.solve(sudoku);
        show.show(sudoku);
    }
    else if (type_sudoku == 3)
    {
        const sudoku_checker_big checker;
        const sudoku_solver_big solver(checker);
        sudoku_generator_big generator(checker, solver);
        sudoku_show_big show;

        int level{};
        std::cout << "Enter level of the sudoku: ";
        std::cin >> level;

        std::array<std::array<int, 16>, 16> sudoku = generator.generate16(level);

        show.show(sudoku);

        solver.solve(sudoku);
        show.show(sudoku);
    }
    else if (type_sudoku == 4)
    {
        const sudoku_checker_samurai checker;
        const sudoku_solver_samurai solver(checker);
        sudoku_generator_samurai generator(checker, solver);
        sudoku_show_samurai show;

        int level{};
        std::cout << "Enter level of the sudoku: ";
        std::cin >> level;

        std::array<std::array<int, 21>, 21> sudoku = generator.generate21(level);

        show.show(sudoku);

        solver.solve(sudoku);
        show.show(sudoku);
    }
    else
    {
        std::cerr << "Unknown sudoku type\n";
        return 1;
    }


    return 0;
}
