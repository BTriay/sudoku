cmake_minimum_required(VERSION 3.21)

project(Sudoku	VERSION 0.1
				DESCRIPTION "Sudoku solver"
				LANGUAGES CXX)
				
add_executable(sudoku
				src/main.cpp
				src/domain/Grid.cpp
				src/domain/Grid.h
				src/utils/io.cpp
				src/utils/io.h
				src/domain/Cell.cpp
				src/domain/Cell.h)

target_compile_features(sudoku PUBLIC cxx_std_20)


# the below is from
# http://google.github.io/googletest/quickstart-cmake.html

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY	https://github.com/google/googletest.git
  GIT_TAG       	3e0e32ba300ce8afe695ad3ba7e81b21b7cf237a #last commit as of 22/11/2021
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(sudoku_tests test/tests.cpp)

target_link_libraries(sudoku_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(sudoku_tests)