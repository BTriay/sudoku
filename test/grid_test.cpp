#include <gtest/gtest.h>

import <array>;

import GridEngine;
import Grid;
import Cell;

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
	
	constexpr auto cell_position = 0;
	EXPECT_EQ(g.cell_solution(cell_position), 1);

	auto same_row = engine::same_row_cells(cell_position);
	auto same_column = engine::same_column_cells(cell_position);
	auto same_block = engine::same_block_cells(cell_position);

	// check INSTANTIATE_TEST_SUITE_P, might replace this loop
	for (auto i = 1; i < engine::array_size; ++i)
	{
		auto cell_position_next_on_row = same_row[i];
		auto cell_position_next_on_column = same_column[i];
		auto cell_position_next_on_block = same_block[i];

		EXPECT_EQ(g.cell_solution(cell_position_next_on_row), engine::impossible_value);
		EXPECT_EQ(g.cell_solution(cell_position_next_on_column), engine::impossible_value);
		EXPECT_EQ(g.cell_solution(cell_position_next_on_block), engine::impossible_value);
	}
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

TEST(GridTests, CheckEasyGrid)
{
	auto input_grid = "045 297 000 \
		017 450 008 \
		200 000 750 \
		000 109 300 \
		500 020 006 \
		006 705 000 \
		084 000 001 \
		700 048 230 \
		000 916 840";

	auto solution = "845 297 613 \
		617 453 928 \
		239 681 754 \
		428 169 375 \
		573 824 196 \
		196 735 482 \
		984 372 561 \
		761 548 239 \
		352 916 847";
	
	auto starting_grid = GridEngine::read_grid_from_string(input_grid);
	starting_grid.find_solution();

	auto solution_grid = GridEngine::read_grid_from_string(solution);
	solution_grid.find_solution();

	EXPECT_EQ(starting_grid, solution_grid);
}

TEST(GridTests, CheckEasyGrid2)
{
	auto input_grid = "090 360 080 \
		608 007 503 \
		350 201 006 \
		245 000 000 \
		006 000 300 \
		000 000 857 \
		500 403 071 \
		709 100 408 \
		010 076 020";

	auto solution = "197 365 284 \
		628 947 513 \
		354 281 796 \
		245 738 169 \
		876 519 342 \
		931 624 857 \
		582 493 671 \
		769 152 438 \
		413 876 925";

	auto starting_grid = GridEngine::read_grid_from_string(input_grid);
	starting_grid.find_solution();

	auto solution_grid = GridEngine::read_grid_from_string(solution);
	solution_grid.find_solution();

	EXPECT_EQ(starting_grid, solution_grid);
}




/*
GridTests todo

pass a grid with...
- a known result, make sure if finds it (probably have several cases)
- non-compatible values, throw an error

pass a row with non-resolved cells, set_solution to one cell, make sure
that the other cells do not have that value anymore

*/