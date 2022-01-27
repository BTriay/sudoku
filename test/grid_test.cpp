#include <gtest/gtest.h>

import <array>;
import <string>;

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
	auto input_grid_str = "045 297 000 \
		017 450 008 \
		200 000 750 \
		000 109 300 \
		500 020 006 \
		006 705 000 \
		084 000 001 \
		700 048 230 \
		000 916 840";

	auto solution_grid_str = "845 297 613 \
		617 453 928 \
		239 681 754 \
		428 169 375 \
		573 824 196 \
		196 735 482 \
		984 372 561 \
		761 548 239 \
		352 916 847";
	
	GridEngine ge("dummy.txt");

	auto input_grid = ge.read_grid_from_string(input_grid_str);
	input_grid.find_solution();

	auto solution_grid = ge.read_grid_from_string(solution_grid_str);
	solution_grid.find_solution();

	EXPECT_EQ(input_grid, solution_grid);
}

TEST(GridTests, CheckEasyGrid2)
{
	auto input_grid_str = "090 360 080 \
		608 007 503 \
		350 201 006 \
		245 000 000 \
		006 000 300 \
		000 000 857 \
		500 403 071 \
		709 100 408 \
		010 076 020";

	auto solution_grid_str = "197 365 284 \
		628 947 513 \
		354 281 796 \
		245 738 169 \
		876 519 342 \
		931 624 857 \
		582 493 671 \
		769 152 438 \
		413 876 925";

	GridEngine ge("dummy.txt");

	auto input_grid = ge.read_grid_from_string(input_grid_str);
	input_grid.find_solution();

	auto solution_grid = ge.read_grid_from_string(solution_grid_str);
	solution_grid.find_solution();

	EXPECT_EQ(input_grid, solution_grid);
}

TEST(GridTests, CheckMediumGrid)
{
	auto input_grid_str = "820 306 000 \
		970 080 105 \
		004 900 000 \
		700 010 000 \
		215 000 683 \
		000 020 001 \
		000 008 700 \
		407 090 016 \
		000 107 058";

	auto solution_grid_str = "821 356 947 \
		973 284 165 \
		564 971 832 \
		738 615 294 \
		215 749 683 \
		649 823 571 \
		156 438 729 \
		487 592 316 \
		392 167 458";

	GridEngine ge("dummy.txt");

	auto input_grid = ge.read_grid_from_string(input_grid_str);
	input_grid.find_solution();

	auto solution_grid = ge.read_grid_from_string(solution_grid_str);
	solution_grid.find_solution();

	EXPECT_EQ(input_grid, solution_grid);
}

TEST(GridTests, CheckMediumGrid2)
{
	auto input_grid_str = "060 074 100 \
		002 009 070 \
		007 830 540 \
		005 000 700 \
		030 905 000 \
		209 007 080 \
		000 710 453 \
		001 090 060 \
		000 000 008";

	auto solution_grid_str = "568 274 139 \
		342 159 876 \
		197 836 542 \
		685 321 794 \
		734 985 621 \
		219 647 385 \
		926 718 453 \
		851 493 267 \
		473 562 918";

	GridEngine ge("dummy.txt");

	auto input_grid = ge.read_grid_from_string(input_grid_str);
	input_grid.find_solution();

	auto solution_grid = ge.read_grid_from_string(solution_grid_str);
	solution_grid.find_solution();

	EXPECT_EQ(input_grid, solution_grid);
}

TEST(GridTests, CheckHardGrid)
{
	auto input_grid_str = "700 090 602 \
		000 102 009 \
		010 700 000 \
		568 000 003 \
		000 683 004 \
		000 005 000 \
		003 050 000 \
		000 800 405 \
		001 000 070";

	auto solution_grid_str = "734 598 612 \
		685 132 749 \
		219 764 358 \
		568 427 193 \
		197 683 524 \
		342 915 867 \
		473 256 981 \
		926 871 435 \
		851 349 276";
	
	GridEngine ge("dummy.txt");

	auto input_grid = ge.read_grid_from_string(input_grid_str);
	input_grid.find_solution();

	auto solution_grid = ge.read_grid_from_string(solution_grid_str);
	solution_grid.find_solution();

	EXPECT_EQ(input_grid, solution_grid);
}

TEST(GridTests, CheckHardGrid2)
{
	auto input_grid_str = "800 009 005 \
		040 000 726 \
		000 030 800 \
		000 047 000 \
		030 050 000 \
		004 090 530 \
		000 070 000 \
		910 020 080 \
		020 005 900";

	auto solution_grid_str = "871 269 345 \
		349 518 726 \
		256 734 891 \
		598 347 162 \
		132 856 479 \
		764 192 538 \
		683 971 254 \
		915 423 687 \
		427 685 913";

	GridEngine ge("dummy.txt");

	auto input_grid = ge.read_grid_from_string(input_grid_str);
	input_grid.find_solution();

	auto solution_grid = ge.read_grid_from_string(solution_grid_str);
	solution_grid.find_solution();

	EXPECT_EQ(input_grid, solution_grid);
}

TEST(GridTests, CheckEvildGrid)
{
	auto input_grid_str = "380 100 070 \
		000 004 200 \
		006 000 000 \
		750 300 080 \
		900 000 000 \
		000 010 003 \
		560 020 700 \
		009 500 000 \
		001 000 060";

	auto simple_solution_grid_str = "385 102 070 \
		197 004 200 \
		426 000 000 \
		752 300 080 \
		913 000 007 \
		648 010 003 \
		564 020 700 \
		009 500 000 \
		001 000 060";

	auto brute_force_solution_grid_str = "385 192 674 \
		197 684 235 \
		426 735 891 \
		752 349 186 \
		913 856 427 \
		648 217 953 \
		564 923 718 \
		879 561 342 \
		231 478 569";

	GridEngine ge("dummy.txt");
	ge.init_grid_from_string(input_grid_str);
	ge.solve_grid();

	auto input_grid = ge.read_grid_from_string(input_grid_str);
	input_grid.find_solution();

	auto simple_solution_grid = ge.read_grid_from_string(simple_solution_grid_str);
	simple_solution_grid.find_solution();

	auto brut_force_solution_grid = ge.read_grid_from_string(brute_force_solution_grid_str);
	brut_force_solution_grid.find_solution();

	EXPECT_EQ(input_grid, simple_solution_grid);
	EXPECT_EQ(ge.solution(), brut_force_solution_grid);
}

TEST(GridTests, CheckEvildGrid2)
{
	auto input_grid_str = "004 000 300 \
		009 800 000 \
		380 010 020 \
		000 006 010 \
		003 000 000 \
		750 400 200 \
		000 040 005 \
		090 000 000 \
		820 500 700";

	auto simple_solution_grid_str = "004 000 300 \
		009 800 000 \
		386 010 020 \
		942 006 010 \
		163 000 000 \
		758 401 200 \
		637 040 005 \
		495 000 002 \
		821 500 700";

	auto brute_force_solution_grid_str = "514 627 389 \
		279 834 651 \
		386 915 427 \
		942 376 518 \
		163 258 974 \
		758 491 236 \
		637 142 895 \
		495 783 162 \
		821 569 743";

	GridEngine ge("dummy.txt");
	ge.init_grid_from_string(input_grid_str);
	ge.solve_grid();

	auto input_grid = ge.read_grid_from_string(input_grid_str);
	input_grid.find_solution();

	auto simple_solution_grid = ge.read_grid_from_string(simple_solution_grid_str);
	simple_solution_grid.find_solution();

	auto brut_force_solution_grid = ge.read_grid_from_string(brute_force_solution_grid_str);
	brut_force_solution_grid.find_solution();

	EXPECT_EQ(input_grid, simple_solution_grid);
	EXPECT_EQ(ge.solution(), brut_force_solution_grid);
}

/*
GridTests todo

pass a grid with...
- non-compatible values, throw an error

pass a row with non-resolved cells, set_solution to one cell, make sure
that the other cells do not have that value anymore

*/