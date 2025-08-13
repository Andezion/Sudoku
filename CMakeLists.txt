cmake_minimum_required(VERSION 3.29)
project(Sudoku)

set(CMAKE_CXX_STANDARD 11)

add_executable(Sudoku main.cpp
        sudoku_classic.h
        sudoku_diagonal.h
        sudoku_generator.h
        sudoku_solver.h)
