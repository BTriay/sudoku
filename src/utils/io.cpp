module io;

import <iostream>;
import <fstream>;
import <sstream>;
import <filesystem>;
import <array>;

bool io::helper::file_exists(const std::string& filename)
{
    if (!std::filesystem::exists(std::filesystem::path { filename }))
    {
        std::cout << "The file specified does not exist:\n\t" << filename << '\n';
        return false;
    }       
    return true;
}

std::optional<std::fstream> io::helper::get_file_stream(const std::string& filename)
{
    if (!file_exists(filename))
        return {};
    
    std::fstream grid{ filename, std::ios::in };
    if (!grid.is_open()) {
        std::cout << "The file " << filename << " could not be opened" << '\n';
        return {};
    }

    return grid;
}

std::optional<std::array<int, io::grid_size>> io::read_grid_from_file(const std::string& filename)
{
    auto fs = helper::get_file_stream(filename);
    if (!fs.has_value())
        return {};

    std::array<int, io::grid_size> res{ };

    auto it = std::begin(res);
    char c;

    while(fs.value().get(c))
    {
        if (isdigit(c))
            *it++ = c - '0';
    }

    return res;
}

std::array<int, io::grid_size> io::read_grid_from_string(const std::string& s)
{
    std::stringstream fs{ s };

    std::array<int, io::grid_size> res{ };

    auto it = std::begin(res);
    char c;

    while (fs >> c)
    {
        if (isdigit(c))
            *it++ = c - '0';
    }

    return res;
}
