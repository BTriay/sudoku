#ifndef HEADER_CELL
#define HEADER_CELL

#include <array>
#include <algorithm>

class Cell
{
public:
	constexpr static int value_lower_bound = 1;
	constexpr static int value_upper_bound = 9;
	constexpr static int array_size = value_upper_bound;
	constexpr static int impossible_value = 0;
	
	Cell(int val = {});

	int solution() const { return m_solution; }
	void set_solution(int val);

	std::array<int, Cell::array_size> possible_values() const;
	bool is_possible_value(int value);
	
	bool remove_possible_value(int val);

private:
	int m_solution;
	std::array<int, Cell::array_size> m_possible_values;

	void remove_all_possible_values();
};

std::array<int, Cell::array_size> common_possible_values(const Cell& lhs, const Cell& rhs);

#endif // !HEADER_CELL
