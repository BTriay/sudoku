#ifndef HEADER_GRID

#include <iostream>
#include <array>

#include ".\Cell.h"

namespace engine
{

	class Grid
	{
	public:
		Grid(std::array<int, Cell::array_size * Cell::array_size> init_values);

#ifdef _DEBUG
		// this is cheating, but allows more tests!
		virtual ~Grid() = default;
		auto cells() const -> decltype(auto) { return m_cells; }
#endif // DEBUG

		int cell_solution(int cell_position) const;

		bool find_solution();
		void clean_from_existing_solution();
		void check_unique_value();
		//void cross_block_constraints();

		void print_possible_cells_values(std::ostream& os);

	private:
		std::array<Cell, Cell::array_size * Cell::array_size> m_cells;

		bool check_unique_values_rows(); /*!< strategy 2 helper */
		bool check_unique_values_columns(); /*!< strategy 2 helper */
		bool check_unique_values_blocks(); /*!< strategy 2 helper */
		bool check_unique_values_area(std::array<int, Cell::array_size> cells_positions); /*!< strategy 2 helper */

		void check_duplicate_solutions(std::array<int, Cell::array_size> cells_positions);
	};

	std::array<int, Cell::array_size> same_row_cells(int cell_position);
	std::array<int, Cell::array_size> same_column_cells(int cell_position);
	std::array<int, Cell::array_size> same_block_cells(int cell_position);

	std::ostream& operator<<(std::ostream& os, const Grid& g);

}

#endif // !HEADER_GRID