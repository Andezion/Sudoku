cmake_minimum_required(VERSION 3.29)
project(Sudoku)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_PATH "C:/raylib/raylib")

add_subdirectory(${RAYLIB_PATH} ${CMAKE_BINARY_DIR}/raylib_build)

add_executable(Sudoku
        main.cpp
        sudoku_generator.h
        sudoku_solver.h
        sudoku_checker.h
        sudoku_show.h
)

target_link_libraries(Sudoku raylib)

if (WIN32)
    target_link_libraries(Sudoku winmm)
endif()
