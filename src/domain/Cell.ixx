export module Cell;

import <array>;
import <algorithm>;

export namespace engine
{
	constexpr static int value_lower_bound = 1;
	constexpr static int value_upper_bound = 9;
	constexpr static int array_size = value_upper_bound;
	constexpr static int impossible_value = 0;

	using arr9int = std::array<int, array_size>;
	using arr81int = std::array<int, array_size * array_size>;
}

export class Cell
{
public:
	
	Cell(int val = {});

	int solution() const { return m_solution; }
	void set_solution(int val);

	engine::arr9int possible_values() const;
	bool is_possible_value(int value);
	
	bool remove_possible_value(int val);

private:
	int m_solution;
	engine::arr9int m_possible_values;

	void remove_all_possible_values();
};


export engine::arr9int common_possible_values(const Cell& lhs, const Cell& rhs);

export constexpr engine::arr9int zero_init_array()
{
	return engine::arr9int{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

export constexpr engine::arr9int iota_init_array()
{
	return engine::arr9int{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
}
