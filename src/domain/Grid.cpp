#include "Grid.h"

#include <numeric>
#include <algorithm>

using std::begin;
using std::end;

engine::Grid::Grid(std::array<int, Cell::array_size * Cell::array_size> init_values)
{
	for (auto i = 0; i < Cell::array_size * Cell::array_size; ++i)
	{
		m_cells[i] = Cell(init_values[i]);
	}
}

int engine::Grid::cell_solution(int cell_position) const
{
	return std::max(m_cells[cell_position].solution(), Cell::impossible_value);
}

template <typename F>
struct ApplyFunctionRows : F
{
	ApplyFunctionRows(F f) : F(std::move(f)) {}
	using F::operator();
};

bool engine::Grid::find_solution()
{
	clean_from_existing_solution();
	try
	{
		check_unique_value();
	}
	catch (const std::invalid_argument& e)
	{
		return false;
	}
	return true;
}

/*!
strategy #1: simply clean up the possible values based on the existing solution
*/
void engine::Grid::clean_from_existing_solution()
{
	auto new_solution = false;

	for (auto i = 0; i < Cell::array_size * Cell::array_size; ++i)
	{
		if (m_cells[i].solution())
		{
			auto sol = m_cells[i].solution();

			for (auto c : same_row_cells(i))
				new_solution = m_cells[c].remove_possible_value(sol) || new_solution;

			for (auto c : same_column_cells(i))
				new_solution = m_cells[c].remove_possible_value(sol) || new_solution;

			for (auto c : same_block_cells(i))
				new_solution = m_cells[c].remove_possible_value(sol) || new_solution;
		}
	}

	if (new_solution)
		clean_from_existing_solution();
}

/*!
strategy #2: check if a value is possible in a single cell within a row/column/block
 */
void engine::Grid::check_unique_value()
{
	if (check_unique_values_rows())
	{
		clean_from_existing_solution();
		check_unique_value();
	}

	if (check_unique_values_columns())
	{
		clean_from_existing_solution();
		check_unique_value();
	}

	if (check_unique_values_blocks())
	{
		clean_from_existing_solution();
		check_unique_value();
	}
}

bool engine::Grid::check_unique_values_rows()
{
	auto updated_cell = false;
	for (auto i = 0; i < Cell::array_size; ++i)
	{
		updated_cell = check_unique_values_area(same_row_cells(i * 9)) || updated_cell;
	}
	return updated_cell;
}

bool engine::Grid::check_unique_values_columns()
{
	auto updated_cell = false;
	for (auto i = 0; i < Cell::array_size; ++i)
	{
		updated_cell = check_unique_values_area(same_column_cells(i)) || updated_cell;
	}
	return updated_cell;
}

bool engine::Grid::check_unique_values_blocks()
{
	auto updated_cell = false;
	for (auto i = 0; i < 3; ++i)
	{
		for (auto j = 0; j < 3; ++j)
		{
			updated_cell = check_unique_values_area(same_block_cells(i * 3 + j * 27)) || updated_cell;
		}
	}
	return updated_cell;
}

bool engine::Grid::check_unique_values_area(std::array<int, Cell::array_size> cells_positions)
{	
	auto updated_cell = false;

	for (auto value = Cell::value_lower_bound; value <= Cell::value_upper_bound; ++value)
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
	
	check_duplicate_solutions(cells_positions);
	return updated_cell;
}

void engine::Grid::check_duplicate_solutions(std::array<int, Cell::array_size> cells_positions)
{
	for (auto val = Cell::value_lower_bound; val <= Cell::value_upper_bound; ++val)
	{
		auto value_found = false;		
		for (auto cell_position : cells_positions)
		{
			if (m_cells[cell_position].solution() == val)
			{
				if (value_found)
				{
					throw std::invalid_argument("Invalid input grid");
				}
				value_found = true;
			}
		}
	}
}

// #strategy 3


/*
* humm not exactly beautiful. To be cleaned up
*/
void engine::Grid::print_possible_cells_values(std::ostream& os)
{
	for (auto row_first_cell = 0;
		row_first_cell < Cell::array_size * Cell::array_size;
		row_first_cell += 9)
	{
		for (auto row_cell : same_row_cells(row_first_cell))
		{
			os << (m_cells[row_cell].is_possible_value(1) ? "1" : " ");
			os << (m_cells[row_cell].is_possible_value(2) ? "2" : " ");
			os << (m_cells[row_cell].is_possible_value(3) ? "3" : " ");
			if ((row_cell % 3 == 2 || row_cell % 6 == 5) && row_cell % 9 != 8)
				os << " # ";
			else if (row_cell % 9 != 8)
				os << " ' ";
		}
		os << '\n';

		for (auto row_cell : same_row_cells(row_first_cell))
		{
			os << (m_cells[row_cell].is_possible_value(4) ? "4" : " ");
			os << (m_cells[row_cell].is_possible_value(5) ? "5" : " ");
			os << (m_cells[row_cell].is_possible_value(6) ? "6" : " ");
			if ((row_cell % 3 == 2 || row_cell % 6 == 5) && row_cell % 9 != 8)
				os << " # ";
			else if (row_cell % 9 != 8)
				os << " ' ";
		}
		os << '\n';

		for (auto row_cell : same_row_cells(row_first_cell))
		{
			os << (m_cells[row_cell].is_possible_value(7) ? "7" : " ");
			os << (m_cells[row_cell].is_possible_value(8) ? "8" : " ");
			os << (m_cells[row_cell].is_possible_value(9) ? "9" : " ");
			if ((row_cell % 3 == 2 || row_cell % 6 == 5) && row_cell % 9 != 8)
				os << " # ";
			else if (row_cell % 9 != 8)
				os << " ' ";
		}
		os << '\n';

		if (row_first_cell == 18 || row_first_cell == 45)
			os << "#####################################################\n";
		else if (row_first_cell != 72)
			os << "-----------------------------------------------------\n";
	}
}

std::array<int, Cell::array_size> engine::same_row_cells(int cell_position)
{
	std::array<int, Cell::array_size> res{};
	std::iota(begin(res), end(res), (cell_position / 9) * 9);
	return res;
}

std::array<int, Cell::array_size> engine::same_column_cells(int cell_position)
{
	std::array<int, Cell::array_size> res{};

	const auto init_value = cell_position % 9;
	for (auto i = 0; i < Cell::array_size; ++i)
	{
		res[i] = init_value + i * 9;
	}

	return res;
}

std::array<int, Cell::array_size> engine::same_block_cells(int cell_position)
{
	std::array<int, Cell::array_size> res{};

	// there must be a simpler way..
	const auto top_left = (cell_position / 27) * 27;
	const auto offset = (((cell_position - top_left) % 9) / 3) * 3;
	const auto init_value = top_left + offset;

	std::iota(begin(res), begin(res) + 3, init_value);
	std::iota(begin(res) + 3, begin(res) + 6, init_value + 9);
	std::iota(begin(res) + 6, end(res), init_value + 18);

	return res;
}

std::ostream& engine::operator<<(std::ostream& os, const Grid& g)
{
	os << '\n';

	for (auto row = 0; row < Cell::array_size; ++row)
	{
		for (auto column = 0; column < Cell::array_size; ++column)
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
