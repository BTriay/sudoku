export module io;

import <string>;
import <optional>;

export namespace io
{
	namespace helper
	{
	bool file_exists(const std::string& filename);

	std::optional<std::fstream> get_file_stream(const std::string& filename);	
	
	}

	constexpr int grid_size = 81;

	std::optional<std::array<int, grid_size>> read_grid_from_file(const std::string& filename);
	std::array<int, grid_size> read_grid_from_string(const std::string& s);

}