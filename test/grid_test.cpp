#include <gtest/gtest.h>

#include "../src/domain/Grid.cpp"

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