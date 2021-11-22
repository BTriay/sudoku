#ifndef HEADER_GRID

#include <iostream>
#include <array>

#include ".\Cell.h"

namespace engine
{

	class Grid
	{
	public:
		Grid(std::array<int, 81> init_values);

		int cell_solution(int cell_position) const;

		void clean_from_existing_solution();
		void check_unique_value();

	private:
		std::array<Cell, 81> m_cells;

		bool check_unique_values_rows(); /*!< strategy 2 helper */
		bool check_unique_values_columns(); /*!< strategy 2 helper */
		bool check_unique_values_blocks(); /*!< strategy 2 helper */
		bool check_unique_values_area(std::array<int, 9> cells_positions); /*!< strategy 2 helper */

	};

	std::array<int, 9> same_row_cells(int cell_position);
	std::array<int, 9> same_column_cells(int cell_position);
	std::array<int, 9> same_block_cells(int cell_position);

	std::ostream& operator<<(std::ostream& os, const Grid& g);

}

#endif // !HEADER_GRID