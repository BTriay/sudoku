#include <gtest/gtest.h>

#include "../src/domain/Grid.h"
#include "../src/domain/Cell.h"

class TestGrid : public engine::Grid
{
public:
	TestGrid(std::array<int, Cell::array_size* Cell::array_size> init_values) :
		Grid{init_values} {}
};

constexpr std::array<int, Cell::array_size * Cell::array_size> grid_one_value 
	= {1};

constexpr std::array<int, Cell::array_size* Cell::array_size> grid_eight_values
	= { 1, 2, 3, 4, 5, 6, 7, 8 };


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

TEST(GridTests, CleanExistingSolution1)
{
	TestGrid grid{ grid_one_value };
	grid.clean_from_existing_solution();

	auto cells = grid.cells();
	constexpr std::array<int, Cell::array_size> cell_two_possible_values
		= { 0, 2, 3, 4, 5, 6, 7, 8, 9 };


	EXPECT_EQ(cell_two_possible_values, cells[1].possible_values());
}

TEST(GridTests, CleanExistingSolution2)
{
	TestGrid grid{ grid_eight_values };
	grid.clean_from_existing_solution();

	auto cells = grid.cells();

	EXPECT_EQ(cells[8].solution(), 9);
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