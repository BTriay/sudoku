#include <gtest/gtest.h>

#include "../src/domain/Grid.h"
#include "../src/domain/Cell.h"

class TestGrid : public engine::Grid
{
public:
	TestGrid(engine::arr81int init_values) :
		Grid{init_values} {}
};

constexpr engine::arr81int grid_one_value = {1};

constexpr engine::arr81int grid_eight_values = { 1, 2, 3, 4, 5, 6, 7, 8 };

constexpr engine::arr81int grid_one_possible_value
	= { 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0};


TEST(GridTests, CellSolution)
{
	engine::Grid g{ grid_one_value };
	EXPECT_EQ(g.cell_solution(0), 1);
	EXPECT_EQ(g.cell_solution(1), engine::impossible_value); //2nd cell from the same row
	EXPECT_EQ(g.cell_solution(9), engine::impossible_value); //2nd cell from the same column
	EXPECT_EQ(g.cell_solution(19), engine::impossible_value); //cell from the same block
}

TEST(GridTests, SameAreaValues)
{
	constexpr engine::arr9int first_row
		= {0, 1, 2, 3, 4, 5, 6, 7, 8};
	constexpr engine::arr9int first_column
		= { 0, 9, 18, 27, 36, 45, 54, 63, 72 };
	constexpr engine::arr9int first_block
		= { 0, 1, 2, 9, 10, 11, 18, 19, 20 };

	auto r = engine::same_row_cells(0);
	auto c = engine::same_column_cells(0);
	auto b = engine::same_block_cells(0);

	EXPECT_EQ(r, first_row);
	EXPECT_EQ(c, first_column);
	EXPECT_EQ(b, first_block);


	constexpr engine::arr9int sixth_row
		= { 45, 46, 47, 48, 49, 50, 51, 52, 53 };
	constexpr engine::arr9int fifth_column
		= { 4, 13, 22, 31, 40, 49, 58, 67, 76 };
	constexpr engine::arr9int middle_block
		= { 30, 31, 32, 39, 40, 41, 48, 49, 50 };

	r = engine::same_row_cells(49);
	c = engine::same_column_cells(49);
	b = engine::same_block_cells(49);

	EXPECT_EQ(r, sixth_row);
	EXPECT_EQ(c, fifth_column);
	EXPECT_EQ(b, middle_block);

}

TEST(GridTests, CleanExistingSolution1)
{
	TestGrid grid{ grid_one_value };
	grid.clean_from_existing_solution();

	auto cells = grid.cells();
	constexpr engine::arr9int cell_two_possible_values
		= { 0, 2, 3, 4, 5, 6, 7, 8, 9 };

	EXPECT_EQ(cell_two_possible_values, cells[1].possible_values());
}

TEST(GridTests, CleanExistingSolution2)
{
	TestGrid grid{ grid_eight_values };
	grid.clean_from_existing_solution();

	const auto cells = grid.cells();

	EXPECT_EQ(cells[8].solution(), 9);

	constexpr engine::arr9int first_block_possibles_values
		= { 0, 0, 0, 4, 5, 6, 7, 8, 9 };
	EXPECT_EQ(cells[9].possible_values(), first_block_possibles_values);

	EXPECT_EQ(cells[9].solution(), engine::impossible_value);
}

TEST(GridTests, CheckUniqueValue)
{
	TestGrid grid{ grid_one_possible_value };
	
	grid.clean_from_existing_solution();
	grid.check_unique_value();

	const auto cells = grid.cells();

	EXPECT_EQ(cells[0].solution(), 1);
}

/*
GridTests todo

pass a grid with...
- a known result, make sure if finds it (probably have several cases)
- non-compatible values, throw an error

pass a row with non-resolved cells, set_solution to one cell, make sure
that the other cells do not have that value anymore

*/