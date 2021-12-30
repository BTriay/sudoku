module GridEngine;

import <string>;

import Grid;
import io;

engine::Grid GridEngine::read_grid_from_file(const std::string& filename)
{
    auto grid_array = io::read_txt_grid(filename);

    if (!grid_array.has_value())
        throw std::invalid_argument("Invalid filename");

    engine::Grid g{ grid_array.value() };

    return g;
}
