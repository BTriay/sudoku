import <iostream>;
import <fstream>;
import <string>;

#include "utils\io.h"
#include "domain\Grid.h"

int main(int argc, char* argv[])
{
    
    std::string filename;
    if (argc > 1)
    {
        filename = argv[1];
    }
    else {
        filename = "input_grid.txt";
    }
    
    auto grid_array = io::read_txt_grid(filename);

    if (!grid_array.has_value())
        return 1;

    engine::Grid g{ grid_array.value()};

    std::fstream fs{ "output_grid.txt", std::ios::out };
    fs << "Starting grid:\n";
    fs << g;
    
    if (!g.find_solution())
    {
        std::cout << "Invalid input grid\n";
        return 1;
    }
    
    fs << "\nSolution found:\n";
    fs << g;

    fs << "\nPossible values:\n\n";
    g.print_possible_cells_values(fs);

}