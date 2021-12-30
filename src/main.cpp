import <iostream>;
import <fstream>;
import <string>;
import <array>;

import io;
import Grid;
import GridEngine;

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
    
    auto g = GridEngine::read_grid_from_file(filename);

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