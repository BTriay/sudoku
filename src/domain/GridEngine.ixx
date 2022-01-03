export module GridEngine;

import <string>;

import Grid;

export class GridEngine
{
public:
	GridEngine();
	~GridEngine();

	engine::Grid read_grid_from_file(const std::string& filename);
	engine::Grid read_grid_from_string(const std::string& s);

private:
	engine::Grid last_valid_grid;

	static inline int engine_count = 0;
};