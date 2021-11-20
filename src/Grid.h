#ifndef HEADER_GRID

#include <iostream>
#include <array>

#include "./domain/Cell.h"

namespace engine
{

	class Grid
	{
	public:
		Grid(std::array<int, 81> init_values);

		int cell_solution(int cell_position) const;

	private:
		std::array<Cell, 81> m_cells;

	};

	std::array<int, 9> same_row_cells(int cell_position);
	std::array<int, 9> same_column_cells(int cell_position);
	std::array<int, 9> same_block_cells(int cell_position);

	std::ostream& operator<<(std::ostream& os, const Grid& g);

}

#endif // !HEADER_GRID