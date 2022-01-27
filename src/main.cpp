import <fstream>;

import io;
import Grid;
import GridEngine;

int main(int argc, char* argv[])
{
    auto input_filename = "input_grid.txt";
    auto output_filename = "output_grid.txt";

    GridEngine ge{ output_filename };

    // strategies 1 & 2
    //auto fs = std::fstream{ output_filename, std::ios::out };

    //auto g = ge.read_grid_from_file(input_filename);
    //fs << "Starting grid:\n" << g;

    //g.find_solution();
    //fs << "Strategy 1 & 2 solution:\n" << g;
    
    // strategies 1 & 2 + brute force
    ge.init_grid_from_file(input_filename);
    ge.solve_grid();
}