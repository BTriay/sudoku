#include <gtest/gtest.h>

#include "../src/domain/Grid.h"
#include "../src/domain/Cell.h"

constexpr std::array<int, Cell::array_size * Cell::array_size> grid_one_value 
	= {1};

TEST(GridTests, CellSolution)
{
	engine::Grid g{ grid_one_value };
	EXPECT_EQ(g.cell_solution(0), 1);
	EXPECT_EQ(g.cell_solution(1), Cell::impossible_value); //2nd cell from the same row
	EXPECT_EQ(g.cell_solution(9), Cell::impossible_value); //2nd cell from the same column
	EXPECT_EQ(g.cell_solution(19), Cell::impossible_value); //cell from the same block
}

TEST(GridTests, SameAreaValues)
{
	engine::Grid g{ grid_one_value };
	
	constexpr std::array<int, Cell::array_size> first_row 
		= {0, 1, 2, 3, 4, 5, 6, 7, 8};
	constexpr std::array<int, Cell::array_size> first_column
		= { 0, 9, 18, 27, 36, 45, 54, 63, 72 };
	constexpr std::array<int, Cell::array_size> first_block
		= { 0, 1, 2, 9, 10, 11, 18, 19, 20 };

	const auto r = engine::same_row_cells(0);
	const auto c = engine::same_column_cells(0);
	const auto b = engine::same_block_cells(0);

	EXPECT_EQ(r, first_row);
	EXPECT_EQ(c, first_column);
	EXPECT_EQ(b, first_block);
}


/*
GridTests todo

pass a grid with...
- a single non-zero value, only one cell udpated accordingly
- a known result, make sure if finds it (probably have several cases)
- non-compatible values, throw an error

pass a row / column / block with a value possible in only one cell
=> becomes the solution to the cell

pass a row with non-resolved cells, set_solution to one cell, make sure
that the other cells do not have that value anymore

*/