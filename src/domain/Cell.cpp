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
		std::iota(begin(m_possible_values), end(m_possible_values), 0);
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
	std::array<int, 9> res{ m_possible_values };
	
	return res;
}

void Cell::remove_possible_value(int val)
{
	if (0 < val && val < 10)
		m_possible_values[val-1] = 0;
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
