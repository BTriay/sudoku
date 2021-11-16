#include <string>
#include <optional>

namespace io
{
	namespace helper
	{
	bool file_exists(const std::string& filename);

	std::optional<std::fstream> get_file_stream(const std::string& filename);
	}

	const int grid_size = 81;

	std::optional<std::array<int, grid_size>> read_txt_grid(const std::string& filename);

}