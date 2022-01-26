export module Grid;

import <iostream>;
import <array>;
import <vector>;
import <concepts>;

import Cell;

export namespace engine
{

	class Grid
	{
	public:
		Grid() = default;
		Grid(std::array<int, engine::array_size * engine::array_size> init_values);

#ifdef _DEBUG
		// this is cheating, but allows more tests!
		virtual ~Grid() = default;

		auto cells() const -> decltype(auto) { return m_cells; }
#endif // DEBUG

		int cell_solution(int cell_position) const;

		bool find_solution();
		void clean_from_existing_solution();
		void check_unique_value();
		std::vector<engine::Grid> next_grids_to_try() const;

		bool grid_solved() const;
		void print_possible_cells_values(std::ostream& os);

	private:
		std::array<Cell, engine::array_size * engine::array_size> m_cells;

		template <typename Func>
		bool do_on_rows(Func f);

		template <typename Func>
		bool do_on_columns(Func f);

		template <typename Func>
		bool do_on_blocks(Func f);

		bool check_unique_values_area(engine::arr9int cells_positions); /*!< strategy 2 helper */
		bool check_duplicate_solutions(engine::arr9int cells_positions);
	};

	// non-member functions
	engine::arr9int same_row_cells(int cell_position);
	engine::arr9int same_column_cells(int cell_position);
	engine::arr9int same_block_cells(int cell_position);

	std::ostream& operator<<(std::ostream& os, const Grid& g);

	inline bool operator==(const Grid& lhs, const Grid& rhs)
	{
		auto res = true;
		for (auto i = 0; i < engine::array_size * engine::array_size; ++i)
		{
			res = (lhs.cell_solution(i) == rhs.cell_solution(i)) && res;
		}		
		return res;
	}

	// member functions
	template<typename Func>
	inline bool Grid::do_on_rows(Func f)
	{
		auto updated_cell = false;
		for (auto i = 0; i < engine::array_size; ++i)
		{
			updated_cell = (this->*f)(same_row_cells(i * 9)) || updated_cell;
		}
		return updated_cell;
	}

	template<typename Func>
	inline bool Grid::do_on_columns(Func f)
	{
		auto updated_cell = false;
		for (auto i = 0; i < engine::array_size; ++i)
		{
			updated_cell = (this->*f)(same_column_cells(i)) || updated_cell;
		}
		return updated_cell;
	}

	template<typename Func>
	inline bool Grid::do_on_blocks(Func f)
	{
		auto updated_cell = false;
		for (auto i = 0; i < 3; ++i)
		{
			for (auto j = 0; j < 3; ++j)
			{
				updated_cell = (this->*f)(same_block_cells(i * 3 + j * 27)) || updated_cell;
			}
		}
		return updated_cell;
	}

}
