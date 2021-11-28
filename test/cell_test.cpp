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