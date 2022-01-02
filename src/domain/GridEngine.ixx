export module GridEngine;

import <string>;

import Grid;

export class GridEngine
{
public:
	
	static engine::Grid read_grid_from_file(const std::string& filename);
	static engine::Grid read_grid_from_string(const std::string& s);
private:

};