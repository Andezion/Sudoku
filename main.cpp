#include <chrono>

// #include "sudoku_classic.h"
// #include "sudoku_diagonal.h"

#include "sudoku_generator.h"

// void test_classic_sudoku_1()
// {
//     char sudoku[9][9]{};
//     const auto start = std::chrono::high_resolution_clock::now();
//
//     sudoku_classic sudoku_classic(sudoku);
//     sudoku_classic.create_sudoku();
//     sudoku_classic.init_sudoku_easy();
//     // sudoku_classic.print_sudoku();
//     const int res = sudoku_classic.sudoku_solver();
//
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> elapsed_seconds = end - start;
//
//     if (res != -1)
//     {
//         std::cout << "Test2 is PASSED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Test2 is FAILED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     std::cout << '\n';
// }
// void test_classic_sudoku_2()
// {
//     char sudoku[9][9]{};
//     const auto start = std::chrono::high_resolution_clock::now();
//
//     sudoku_classic sudoku_classic(sudoku);
//     sudoku_classic.create_sudoku();
//     sudoku_classic.init_sudoku_medium();
//     // sudoku_classic.print_sudoku();
//     const int res = sudoku_classic.sudoku_solver();
//
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> elapsed_seconds = end - start;
//
//     if (res != -1)
//     {
//         std::cout << "Test2 is PASSED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Test2 is FAILED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     std::cout << '\n';
// }
// void test_classic_sudoku_3()
// {
//     char sudoku[9][9]{};
//     const auto start = std::chrono::high_resolution_clock::now();
//
//     sudoku_classic sudoku_classic(sudoku);
//     sudoku_classic.create_sudoku();
//     sudoku_classic.init_sudoku_basic();
//     // sudoku_classic.print_sudoku();
//     const int res = sudoku_classic.sudoku_solver();
//
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> elapsed_seconds = end - start;
//     std::cout << "Took: " << elapsed_seconds.count() << " seconds." << std::endl;
//
//     if (res != -1)
//     {
//         std::cout << "Test2 is PASSED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Test2 is FAILED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     std::cout << '\n';
// }
//
// void test_classic_sudoku_4()
// {
//     char sudoku[9][9]{};
//     const auto start = std::chrono::high_resolution_clock::now();
//
//     sudoku_classic sudoku_classic(sudoku);
//     sudoku_classic.create_sudoku();
//     sudoku_classic.init_sudoku_hard();
//     // sudoku_classic.print_sudoku();
//     const int res = sudoku_classic.sudoku_solver();
//
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> elapsed_seconds = end - start;
//     std::cout << "Took: " << elapsed_seconds.count() << " seconds." << std::endl;
//
//     if (res != -1)
//     {
//         std::cout << "Test2 is PASSED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Test2 is FAILED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     std::cout << '\n';
// }
// void test_classic_sudoku_5()
// {
//     char sudoku[9][9]{};
//     const auto start = std::chrono::high_resolution_clock::now();
//
//     sudoku_classic sudoku_classic(sudoku);
//     sudoku_classic.create_sudoku();
//     sudoku_classic.init_sudoku_almost_empty();
//     // sudoku_classic.print_sudoku();
//     const int res = sudoku_classic.sudoku_solver();
//
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> elapsed_seconds = end - start;
//     std::cout << "Took: " << elapsed_seconds.count() << " seconds." << std::endl;
//
//     if (res != -1)
//     {
//         std::cout << "Test2 is PASSED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Test2 is FAILED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     std::cout << '\n';
// }
// void test_classic_sudoku_6()
// {
//     char sudoku[9][9]{};
//     const auto start = std::chrono::high_resolution_clock::now();
//
//     sudoku_classic sudoku_classic(sudoku);
//     sudoku_classic.create_sudoku();
//     sudoku_classic.init_sudoku_symmetric();
//     // sudoku_classic.print_sudoku();
//     const int res = sudoku_classic.sudoku_solver();
//
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> elapsed_seconds = end - start;
//     std::cout << "Took: " << elapsed_seconds.count() << " seconds." << std::endl;
//
//     if (res != -1)
//     {
//         std::cout << "Test2 is PASSED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Test2 is FAILED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     std::cout << '\n';
// }
// void test_classic_sudoku_7()
// {
//     char sudoku[9][9]{};
//     const auto start = std::chrono::high_resolution_clock::now();
//
//     sudoku_classic sudoku_classic(sudoku);
//     sudoku_classic.create_sudoku();
//     sudoku_classic.init_sudoku_multiple_solutions();
//     // sudoku_classic.print_sudoku();
//     const int res = sudoku_classic.sudoku_solver();
//
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> elapsed_seconds = end - start;
//     std::cout << "Took: " << elapsed_seconds.count() << " seconds." << std::endl;
//
//     if (res != -1)
//     {
//         std::cout << "Test2 is PASSED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Test2 is FAILED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     std::cout << '\n';
// }
// void test_classic_sudoku_8()
// {
//     char sudoku[9][9]{};
//     const auto start = std::chrono::high_resolution_clock::now();
//
//     sudoku_classic sudoku_classic(sudoku);
//     sudoku_classic.create_sudoku();
//     sudoku_classic.init_sudoku_extreme_hard();
//     // sudoku_classic.print_sudoku();
//     const int res = sudoku_classic.sudoku_solver();
//
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> elapsed_seconds = end - start;
//     std::cout << "Took: " << elapsed_seconds.count() << " seconds." << std::endl;
//
//     if (res != -1)
//     {
//         std::cout << "Test2 is PASSED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     else
//     {
//         std::cout << "Test2 is FAILED\nTook: " << elapsed_seconds.count() << " seconds and " + std::to_string(res) + " cycles!" << std::endl;
//     }
//     std::cout << '\n';
// }

int main()
{
    // test_classic_sudoku_1();
    // test_classic_sudoku_2();
    // test_classic_sudoku_3();
    // test_classic_sudoku_4();
    // test_classic_sudoku_5();
    // test_classic_sudoku_6();
    // test_classic_sudoku_7();
    // test_classic_sudoku_8();

    sudoku_generator *sudoku = nullptr;
    int type;
    std::cin >> type;

    if (type == 1)
    {
        sudoku = new sudoku_classic();
    }
    else if (type == 2)
    {
        sudoku = new sudoku_diagonal();
    }
    else
    {
        std::__throw_logic_error("Wrong input");
    }

    sudoku->generate(2);
    sudoku->show();

    delete sudoku;
    return 0;
}
