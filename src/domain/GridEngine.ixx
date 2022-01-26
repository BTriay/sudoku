export module GridEngine;

import <fstream>;
import <string>;

import Grid;

export class GridEngine
{
public:
	GridEngine(std::string& output_filename);
	~GridEngine();

	void read_grid_from_file(const std::string& filename);
	void read_grid_from_string(const std::string& s);

	void solve_grid();	

private:
	engine::Grid m_start_grid;
	engine::Grid m_solution_grid;
	std::fstream m_fs;
	
	bool solve_grid(engine::Grid& g);

	static inline int engine_count = 0;
};