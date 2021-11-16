#include "Cell.h"

Cell::Cell(int val)
{
	m_solution = 0;

	if (0 < val && val < 10)
		set_solution(val);
	else
		std::generate(
			std::begin(m_possible_values),
			std::end(m_possible_values),
			[i = 0]() mutable { return ++i; });
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
	
	std::sort(std::begin(res), std::end(res));

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
		std::begin(m_possible_values),
		std::end(m_possible_values),
		[] { return 0; });
}
