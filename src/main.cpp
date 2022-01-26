import <string>;

import io;
import Grid;
import GridEngine;

int main(int argc, char* argv[])
{

    std::string input_filename;
    if (argc > 1)
    {
        input_filename = argv[1];
    }
    else {
        input_filename = "input_grid.txt";
    }

    std::string output_filename = "output_grid.txt";
    
    GridEngine ge{ output_filename };
    ge.read_grid_from_file(input_filename);
    ge.solve_grid();
}