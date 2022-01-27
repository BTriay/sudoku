export module GridEngine;

import <fstream>;
import <string>;

import Grid;

export class GridEngine
{
public:
	GridEngine(std::string output_filename);
	~GridEngine();

	void init_grid_from_file(const std::string& filename);
	static engine::Grid read_grid_from_file(const std::string& filename);

	void init_grid_from_string(const std::string& s);
	static engine::Grid read_grid_from_string(const std::string& s);

	void solve_grid();

#ifdef _DEBUG
	engine::Grid solution() const { return m_solution_grid; }
#endif

private:
	engine::Grid m_start_grid;
	engine::Grid m_solution_grid;
	std::fstream m_fs;
	
	bool solve_grid(engine::Grid& g);

	static inline int engine_count = 0;
};