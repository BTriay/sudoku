#include "Grid.h"

#include <numeric>
#include <algorithm>

using std::begin;
using std::end;

engine::Grid::Grid(std::array<int, 81> init_values)
{
	for (auto i = 0; i < 81; ++i)
	{
		m_cells[i] = Cell(init_values[i]);

	}
}

int engine::Grid::cell_solution(int cell_position) const
{
	return std::max(m_cells[cell_position].solution(), 0);
}

// strategy #1
// simply clean up the possible values based on the existing solution
void engine::Grid::clean_from_existing_solution()
{
	auto new_solution = false;

	for (auto i = 0; i < 81; ++i)
	{
		if (m_cells[i].solution())
		{
			auto sol = m_cells[i].solution();

			for (auto c : same_row_cells(i))
				new_solution = new_solution || m_cells[c].remove_possible_value(sol);

			for (auto c : same_column_cells(i))
				new_solution = new_solution || m_cells[c].remove_possible_value(sol);

			for (auto c : same_block_cells(i))
				new_solution = new_solution || m_cells[c].remove_possible_value(sol);
		}

	}

	if (new_solution)
		clean_from_existing_solution();
}

// strategy #2
// check if a value is possible in a single cell within a row/column/block
void engine::Grid::check_unique_value()
{
	auto updated_cell = false;
	updated_cell = updated_cell || check_unique_values_rows();
	updated_cell = updated_cell || check_unique_values_columns();
	updated_cell = updated_cell || check_unique_values_blocks();
	
	if (updated_cell)
	{
		clean_from_existing_solution();
		check_unique_value();
	}
}

bool engine::Grid::check_unique_values_rows()
{
	auto updated_cell = false;
	for (auto i = 0; i < 9; ++i)
	{
		updated_cell = updated_cell || check_unique_values_area(same_row_cells(i * 9));
	}
	return updated_cell;
}

bool engine::Grid::check_unique_values_columns()
{
	auto updated_cell = false;
	for (auto i = 0; i < 9; ++i)
	{
		updated_cell = updated_cell || check_unique_values_area(same_column_cells(i));
	}
	return updated_cell;
}

bool engine::Grid::check_unique_values_blocks()
{
	auto updated_cell = false;
	for (auto i = 0; i < 9; ++i)
	{
		updated_cell = updated_cell || check_unique_values_area(same_block_cells(i * 3));
	}
	return updated_cell;
}

bool engine::Grid::check_unique_values_area(std::array<int, 9> cells_positions)
{
	auto updated_cell = false;

	for (auto value = 1; value < 10; ++value)
	{
		auto value_found_counter  = 0;
		auto first_cell_with_value = -1;

		for (auto cell_position : cells_positions)
		{
			if (!m_cells[cell_position].is_possible_value(value))
				continue;
			
			++value_found_counter;
			if (value_found_counter == 1)
				first_cell_with_value = cell_position;
		}

		if (value_found_counter == 1)
		{
			m_cells[first_cell_with_value].set_solution(value);
			updated_cell = true;
		}
	}
	
	return updated_cell;
}

std::array<int, 9> engine::same_row_cells(int cell_position)
{
	std::array<int, 9> res{};
	std::iota(begin(res), end(res), (cell_position / 9) * 9);
	return res;
}

std::array<int, 9> engine::same_column_cells(int cell_position)
{
	std::array<int, 9> res{};

	auto init_value = cell_position % 9;
	auto i = 0;
	while (i < 9)
	{
		res[i] = init_value + i * 9;
		++i;
	}

	return res;
}

std::array<int, 9> engine::same_block_cells(int cell_position)
{
	std::array<int, 9> res{};

	// there must be a simpler way..
	auto top_left = (cell_position / 27) * 27;
	auto offset = (((cell_position - top_left) % 9) / 3) * 3;
	auto init_value = top_left + offset;

	std::iota(begin(res), begin(res) + 3, init_value);
	std::iota(begin(res) + 3, begin(res) + 6, init_value + 9);
	std::iota(begin(res) + 6, end(res), init_value + 18);
	
	return res;
}

std::ostream& engine::operator<<(std::ostream& os, const Grid& g)
{
	os << '\n';

	for (auto row = 0; row < 9; ++row)
	{
		for (auto column = 0; column < 9; ++column)
		{
			if (column == 3 || column == 6)
				os << "#";

			if (auto sol = g.cell_solution(row * 9 + column))
				os << sol << " ";
			else
				os << "  ";
		}
		os << '\n';

		if (row == 2 || row == 5)
			os << "###################\n";
	}
	os << '\n';

	return os;
}
