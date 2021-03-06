module Grid;

import <numeric>;
import <algorithm>;
import <string>;
import <initializer_list>;

using std::begin;
using std::end;

engine::Grid::Grid(std::array<int, engine::array_size * engine::array_size> init_values)
{
	for (auto i = 0; i < engine::array_size * engine::array_size; ++i)
	{
		m_cells[i] = Cell(init_values[i]);
	}
}

int engine::Grid::cell_solution(int cell_position) const
{
	return std::max(m_cells[cell_position].solution(), engine::impossible_value);
}

bool engine::Grid::find_solution()
{
	try
	{
		clean_from_existing_solution();
		check_unique_value();
	}
	catch (const std::invalid_argument&)
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

	for (auto i = 0; i < engine::array_size * engine::array_size; ++i)
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

	// in hard grids with no deterministic solutions, more performant to 
	// run this before calling the function recursively ?
	auto check_dupes = &Grid::check_duplicate_solutions;
	do_on_rows(check_dupes); do_on_columns(check_dupes); do_on_blocks(check_dupes);
}

/*!
strategy #2: check if a value is possible in a single cell within a row/column/block
 */
void engine::Grid::check_unique_value()
{
	auto check_unique_value_area_ptr = &Grid::check_unique_values_area;
	
	if (do_on_rows(check_unique_value_area_ptr) 
		|| do_on_columns(check_unique_value_area_ptr) 
		|| do_on_blocks(check_unique_value_area_ptr))
	{
		clean_from_existing_solution();
		check_unique_value();
	}
}

/*!
strategy #3: brute force, return the grids to try next
*/
std::vector<engine::Grid> engine::Grid::next_grids_to_try() const
{
	std::vector<engine::Grid> res;
	
	if (!grid_solved())
	{
		int cell_position{ -1 };
		int number_possible_values{engine::value_upper_bound + 1};

		for (auto i = 0; i < engine::array_size * engine::array_size; ++i)
		{
			auto c = m_cells[i];
			if (c.solution() != engine::impossible_value) continue;

			auto cell_possible_solutions = c.possible_values();
			// todo: review ugly static_cast, warning about int64 loss
			// when doing number_possible_values = count;
			auto count = static_cast<int>(std::count_if(begin(cell_possible_solutions),
				end(cell_possible_solutions),
				[](int i) { return i != engine::impossible_value;  })
				);
				
			if (count < number_possible_values)
			{
				cell_position = i;
				number_possible_values = count;
			}

			if (count == 2) break; //count == 2 is the minimum, no need to continue
		}

		auto pv = m_cells[cell_position].possible_values();
		for (auto v : pv)
		{
			if (v == engine::impossible_value) continue;

			auto ng = *this;
			ng.m_cells[cell_position] = v;
			res.push_back(ng);
		}
	}

	return res;
}

bool engine::Grid::grid_solved() const
{
	auto solved = true;
	for (auto& c : m_cells)
	{
		solved = solved && (c.solution() != 0);
	}
	return solved;
}

bool engine::Grid::check_unique_values_area(engine::arr9int cells_positions)
{	
	auto updated_cell = false;

	for (auto value = engine::value_lower_bound; value <= engine::value_upper_bound; ++value)
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

bool engine::Grid::check_duplicate_solutions(engine::arr9int cells_positions)
{
	for (auto val = engine::value_lower_bound; val <= engine::value_upper_bound; ++val)
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
	
	return true;
}

// #strategy 3
// https://bestofsudoku.com/sudoku-strategy


/*
* humm not exactly beautiful. To be cleaned up
*/
void engine::Grid::print_possible_cells_values(std::ostream& os)
{
	auto print_limits = [&](int row) {
		if ((row % 3 == 2 || row % 6 == 5) && row % 9 != 8)
			os << " # ";
		else if (row % 9 != 8)
			os << " ' ";
	};

	auto print_possible_value = [&](int row, int value) {
		os << (m_cells[row].is_possible_value(value) ? std::to_string(value) : " ");
	};
	
	std::initializer_list<std::initializer_list<int>> rows =
	{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };

	for (auto row_first_cell = 0;
		row_first_cell < engine::array_size * engine::array_size;
		row_first_cell += 9)
	{
		for (auto& range : rows)
		{
			for (auto row_cell : same_row_cells(row_first_cell))
			{
				for (auto value : range)
					print_possible_value(row_cell, value);

				print_limits(row_cell);
			}
			os << '\n';
		}

		if (row_first_cell == 18 || row_first_cell == 45)
			os << "#####################################################\n";
		else if (row_first_cell != 72)
			os << "-----------------------------------------------------\n";
	}
}

engine::arr9int engine::same_row_cells(int cell_position)
{
	engine::arr9int res{};
	std::iota(begin(res), end(res), (cell_position / 9) * 9);
	return res;
}

engine::arr9int engine::same_column_cells(int cell_position)
{
	engine::arr9int res{};

	const auto init_value = cell_position % 9;
	for (auto i = 0; i < engine::array_size; ++i)
	{
		res[i] = init_value + i * 9;
	}

	return res;
}

engine::arr9int engine::same_block_cells(int cell_position)
{
	engine::arr9int res{};

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

	for (auto row = 0; row < engine::array_size; ++row)
	{
		for (auto column = 0; column < engine::array_size; ++column)
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
