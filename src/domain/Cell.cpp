#include <numeric>

#include "Cell.h"

using std::begin;
using std::end;

Cell::Cell(int val)
{
	m_solution = 0;

	if (0 < val && val < 10)
		set_solution(val);
	else
		std::iota(begin(m_possible_values), end(m_possible_values), 1);
}

void Cell::set_solution(int val)
{
	if (0 < val && val < 10)
	{
		m_solution = val;
		remove_all_possible_values();
	}
}

std::array<int, 9> Cell::possible_values() const
{
	return m_possible_values;
}

bool Cell::is_possible_value(int value)
{
	if (0 < value && value < 10)
		return m_possible_values[value-1] != 0;
	
	return false;
}

// return true if we have removed enough values to find the solution
bool Cell::remove_possible_value(int val)
{
	if (0 < val && val < 10)
	{
		if (m_possible_values[val - 1] == 0)
			return false;
		
		m_possible_values[val - 1] = 0;
	}

	auto count = std::count(begin(m_possible_values), end(m_possible_values), 0);
	if (count == 8)
	{
		set_solution(std::accumulate(begin(m_possible_values), end(m_possible_values), 0));
		return true;
	}

	return false;
}

void Cell::remove_all_possible_values()
{
	std::generate(
		begin(m_possible_values),
		end(m_possible_values),
		[] { return 0; });
}

std::array<int, 9> common_possible_values(const Cell& lhs, const Cell& rhs)
{
	std::array<int, 9> res{};
	auto lhs_arr = lhs.possible_values();
	auto rhs_arr = rhs.possible_values();

	auto i = 0;
	while (i < 9)
	{
		if (lhs_arr[i] && lhs_arr[i] == rhs_arr[i])
			res[i] = i + 1;
		else
			res[i] = 0;

		++i;
	}

	return res;
}
