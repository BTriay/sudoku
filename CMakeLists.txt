cmake_minimum_required(VERSION 3.21)

project(Sudoku	VERSION 0.1
				DESCRIPTION "Sudoku solver"
				LANGUAGES CXX)
				
add_subdirectory("${PROJECT_SOURCE_DIR}/src/domain")

add_executable(sudoku
				src/main.cpp
				src/domain/Grid.h
				src/utils/io.cpp
				src/utils/io.ixx
				src/domain/Cell.h)

target_link_libraries(sudoku PUBLIC Sudobjects)

target_include_directories(sudoku PUBLIC
				"${PROJECT_BINARY_DIR}"
				"${PROJECT_SOURCE_DIR}/Sudobjects")


if (MSVC)
	add_compile_options(/W4 /WX /MDd /EHsc /experimental:module)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

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

add_executable(sudoku_tests
				test/cell_test.cpp
				test/grid_test.cpp)

target_link_libraries(sudoku_tests gtest_main Sudobjects)

target_include_directories(sudoku_tests PUBLIC
				"${PROJECT_BINARY_DIR}"
				"${PROJECT_SOURCE_DIR}/Sudobjects")

include(GoogleTest)
gtest_discover_tests(sudoku_tests)