#include <iostream>
#include <string>

#include <array>

#include "utils\io.h"

int main(int argc, char* argv[])
{
    
    std::string filename;
    if (argc > 1)
    {
        filename = argv[1];
    }
    else {
        filename = "../../test/grid.txt";
    }
    
    auto grid_array = io::read_txt_grid(filename);

    if (!grid_array.has_value())
    {
        std::cout << "no value\n";
        return 1;
    }

    for (const auto& v : grid_array.value())
        std::cout << v << ", ";


}