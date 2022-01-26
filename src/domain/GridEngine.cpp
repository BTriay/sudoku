module GridEngine;

import Grid;
import io;

GridEngine::GridEngine(std::string& output_filename) : 
    m_start_grid{}, m_solution_grid{}
{
    if (engine_count == 0)
    {
        ++engine_count;
        m_fs = std::fstream { output_filename, std::ios::out };
    }
    else
        throw std::logic_error("The GridEngine can only be initialised once");
}

GridEngine::~GridEngine()
{
    --engine_count;
}

void GridEngine::read_grid_from_file(const std::string& filename)
{
    auto grid_array = io::read_grid_from_file(filename);

    if (!grid_array.has_value())
        throw std::invalid_argument("Invalid filename");

    m_start_grid = grid_array.value();
}

void GridEngine::read_grid_from_string(const std::string& s)
{
    m_start_grid = engine::Grid{ io::read_grid_from_string(s) };
}

void GridEngine::solve_grid()
{
    solve_grid(m_start_grid);
}

bool GridEngine::solve_grid(engine::Grid& g)
{
    m_fs << "Trying to find a solution to the grid:\n" << g;

    if (!g.find_solution())
    {
        m_fs << "Invalid input grid.\n";
        return false;
    }

    if (g.grid_solved())
    {
        m_fs << "Solution found:\n" << g;
        m_solution_grid = g;
        return true;
    }
    else
    {
        m_fs << "The grid could not be solved. Brute force!\n";
        auto next_tries = g.next_grids_to_try();
        for (auto& ng : next_tries)
        {
            if (solve_grid(ng)) return true;
        }

        return false;
    }
}