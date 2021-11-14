cmake_minimum_required(VERSION 3.21)

project(Sudoku	VERSION 0.1
				DESCRIPTION "Sudoku solver"
				LANGUAGES CXX)
				
add_executable(sudoku src/main.cpp src/io.cpp src/io.h)

target_compile_features(sudoku PUBLIC cxx_std_20)