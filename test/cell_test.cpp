#include <gtest/gtest.h>

#include "../src/domain/Cell.cpp"

TEST(CellTests, Constructor)
{
	Cell c{5};
	EXPECT_EQ(5, c.solution());

	auto pv = zero_init_array();
	EXPECT_EQ(pv, c.possible_values());
}

TEST(CellTests, SetSolution)
{
	Cell c;

	EXPECT_EQ(0, c.solution());

	auto pv = iota_init_array();
	EXPECT_EQ(pv, c.possible_values());

	c.set_solution(5);
	EXPECT_EQ(5, c.solution());

	auto pv2 = zero_init_array();
	EXPECT_EQ(pv2, c.possible_values());
}

TEST(CellTests, PossibleValues)
{
	Cell c;

	EXPECT_TRUE(c.is_possible_value(1));
	c.set_solution(2);
	EXPECT_FALSE(c.is_possible_value(1));
}

TEST(CellTests, RemovePossibleValue)
{
	Cell c;
	EXPECT_FALSE(c.remove_possible_value(1));
	EXPECT_FALSE(c.remove_possible_value(2));
	EXPECT_FALSE(c.remove_possible_value(3));
	EXPECT_FALSE(c.remove_possible_value(4));
	EXPECT_FALSE(c.remove_possible_value(5));
	EXPECT_FALSE(c.remove_possible_value(6));
	EXPECT_FALSE(c.remove_possible_value(7));
	EXPECT_TRUE(c.remove_possible_value(8));
	EXPECT_EQ(9, c.solution());
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