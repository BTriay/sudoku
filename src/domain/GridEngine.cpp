module GridEngine;

import <string>;

import Grid;
import io;

GridEngine::GridEngine() : last_valid_grid{}
{
    if (engine_count == 0)
    {
        ++engine_count;
    }
    else
        throw std::logic_error("The GridEngine can only be initialised once");
}

GridEngine::~GridEngine()
{
    --engine_count;
}

engine::Grid GridEngine::read_grid_from_file(const std::string& filename)
{
    auto grid_array = io::read_grid_from_file(filename);

    if (!grid_array.has_value())
        throw std::invalid_argument("Invalid filename");

    last_valid_grid = engine::Grid{ grid_array.value() };

    return last_valid_grid;
}

engine::Grid GridEngine::read_grid_from_string(const std::string& s)
{
    auto grid_array = io::read_grid_from_string(s);

    if (!grid_array.has_value())
        throw std::invalid_argument("Invalid filename");

    last_valid_grid = engine::Grid{ grid_array.value() };

    return last_valid_grid;
}
