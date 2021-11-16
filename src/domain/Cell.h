#ifndef HEADER_CELL
#define HEADER_CELL

#include <array>
#include <algorithm>

class Cell
{
public:
	Cell(int val = {});

	constexpr int solution() { return m_solution; }
	void set_solution(int val);

	std::array<int, 9> possible_values() const;
	
	void remove_possible_value(int val);

private:
	int m_solution;
	std::array<int, 9> m_possible_values;

	void remove_all_possible_values();
};

#endif // !HEADER_CELL
