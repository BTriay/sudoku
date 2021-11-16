#include <iostream>
#include <string>

#include <array>

#include "io.h"

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

    /*for (const auto& v : grid_array.value())
        std::cout << v << ", ";*/

    /*std::fstream s{ filename, s.in };
    if (!s.is_open()) {
        std::cout << "The file " << filename << " could not be opened" << '\n';
        return 1;
    }
    
    char c;
    while (s.get(c))
    {
        
        if (std::isspace(c)) continue;
        std::cout << c << ' - ';
    }*/

}