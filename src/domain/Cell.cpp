#include <numeric>

#include "Cell.h"

using std::begin;
using std::end;

Cell::Cell(int val)
{
	m_solution = Cell::impossible_value;

	if (Cell::value_lower_bound <= val && val <= Cell::value_upper_bound)
		set_solution(val);
	else
		std::iota(begin(m_possible_values), end(m_possible_values), Cell::value_lower_bound);
}

void Cell::set_solution(int val)
{
	if (Cell::value_lower_bound <= val && val <= Cell::value_upper_bound)
	{
		m_solution = val;
		remove_all_possible_values();
	}
}

std::array<int, Cell::array_size> Cell::possible_values() const
{
	return m_possible_values;
}

bool Cell::is_possible_value(int val)
{
	if (Cell::value_lower_bound <= val && val <= Cell::value_upper_bound)
		return m_possible_values[val-1] != Cell::impossible_value;
	
	return false;
}

/*!
return true if we have removed enough values to find the solution
*/
bool Cell::remove_possible_value(int val)
{
	if (Cell::value_lower_bound <= val && val <= Cell::value_upper_bound)
	{
		if (m_possible_values[val - 1] == Cell::impossible_value)
			return false;
		
		m_possible_values[val - 1] = Cell::impossible_value;
	}

	// this will be a problem for the strategy where we try possible solutions
	// because several values could become impossible at once, although only one
	// would be updated in the below logic.
	// need to throw an error somewhere
	if (std::count(begin(m_possible_values), end(m_possible_values), 0) == (Cell::array_size - 1))
	{
		set_solution(std::accumulate(begin(m_possible_values), end(m_possible_values), 0));
		return true;
	}

	return false;
}

void Cell::remove_all_possible_values()
{
	std::fill(begin(m_possible_values), end(m_possible_values), Cell::impossible_value);
}

std::array<int, Cell::array_size> common_possible_values(const Cell& lhs, const Cell& rhs)
{
	std::array<int, Cell::array_size> res{};
	auto lhs_arr = lhs.possible_values();
	auto rhs_arr = rhs.possible_values();

	for (auto i = 0; i < Cell::array_size; ++i)
	{
		if (lhs_arr[i] && lhs_arr[i] == rhs_arr[i])
			res[i] = i + 1;
		else
			res[i] = Cell::impossible_value;
	}

	return res;
}

constexpr std::array<int, Cell::array_size> zero_init_array()
{
	return std::array<int, Cell::array_size> { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

constexpr std::array<int, Cell::array_size> iota_init_array()
{
	return std::array<int, Cell::array_size> { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
}