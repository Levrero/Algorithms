#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <algorithm>
#include <iterator>

// function that checks whether a specific element is a local minimum
bool is_local_min(const std::vector<std::vector<int>> &grid, int i_pos, int j_pos)
{
    int n = grid.size();

    if (i_pos - 1 < 0 && j_pos - 1 < 0)
    {
        if (grid[i_pos][j_pos] < grid[i_pos + 1][j_pos] && grid[i_pos][j_pos] < grid[i_pos][j_pos + 1])
        {
            return true;
        }
    }
    else if (i_pos + 1 >= n && j_pos - 1 < 0)
    {
        if (grid[i_pos][j_pos] < grid[i_pos - 1][j_pos] && grid[i_pos][j_pos] < grid[i_pos][j_pos + 1])
        {
            return true;
        }
    }
    else if (i_pos - 1 < 0 && j_pos + 1 >= n)
    {
        if (grid[i_pos][j_pos] < grid[i_pos + 1][j_pos] && grid[i_pos][j_pos] < grid[i_pos][j_pos - 1])
        {
            return true;
        }
    }
    else if (i_pos + 1 >= n && j_pos + 1 >= n)
    {
        if (grid[i_pos][j_pos] < grid[i_pos - 1][j_pos] && grid[i_pos][j_pos] < grid[i_pos][j_pos - 1])
        {
            return true;
        }
    }
    else if (i_pos - 1 < 0)
    {
        if (grid[i_pos][j_pos] < grid[i_pos + 1][j_pos] && grid[i_pos][j_pos] < grid[i_pos][j_pos - 1] &&
            grid[i_pos][j_pos] < grid[i_pos][j_pos + 1])
        {
            return true;
        }
    }
    else if (i_pos + 1 >= n)
    {
        if (grid[i_pos][j_pos] < grid[i_pos - 1][j_pos] && grid[i_pos][j_pos] < grid[i_pos][j_pos - 1] &&
            grid[i_pos][j_pos] < grid[i_pos][j_pos + 1])
        {
            return true;
        }
    }
    else if (j_pos - 1 < 0)
    {
        if (grid[i_pos][j_pos] < grid[i_pos][j_pos + 1] && grid[i_pos][j_pos] < grid[i_pos - 1][j_pos] &&
            grid[i_pos][j_pos] < grid[i_pos + 1][j_pos])
        {
            return true;
        }
    }
    else if (j_pos + 1 >= n)
    {
        if (grid[i_pos][j_pos] < grid[i_pos][j_pos - 1] && grid[i_pos][j_pos] < grid[i_pos - 1][j_pos] &&
            grid[i_pos][j_pos] < grid[i_pos + 1][j_pos])
        {
            return true;
        }
    }
    else
    {
        if (grid[i_pos][j_pos] < grid[i_pos - 1][j_pos] && grid[i_pos][j_pos] < grid[i_pos + 1][j_pos] &&
            grid[i_pos][j_pos] < grid[i_pos][j_pos - 1] && grid[i_pos][j_pos] < grid[i_pos][j_pos + 1])
        {
            return true;
        }
    }

    return false;
}

// function that forms subgrid
std::vector<std::vector<int>> big_grid_to_small_grid(const std::vector<std::vector<int>> &grid,
    int i_min, int i_max, int j_min, int j_max)
{
    std::vector<int> vector_grid(j_max - j_min);
    std::vector<std::vector<int>> subgrid = {};
    for (int ii = i_min; ii < i_max; ++ii)
    {
        subgrid.push_back(vector_grid);
    }

    for (int ii = i_min; ii < i_max; ++ii)
    {
        for (int jj = j_min; jj < j_max; ++jj)
        {
            subgrid[ii - i_min][jj - j_min] = grid[ii][jj];
        }
    }

    return subgrid;
}

// local minimum function
int local_min(const std::vector<std::vector<int>> &grid)
{
    int n = grid.size();

    // output grid
    for (int ii = 0; ii < n; ++ii)
    {
        for (int jj = 0; jj < n; ++jj)
        {
            std::cout << grid[ii][jj] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "=======================" << std::endl;

    if (n <= 2)
    {
        if (n == 1)
        {
            return grid[0][0];
        }
        else
        {
            int a = grid[0][0];
            int b = grid[0][1];
            int c = grid[1][0];
            int d = grid[1][1];

            return std::min(std::min(std::min(a, b), c), d);
        }   
    }
    else
    {
        // form subgrids
        std::vector<std::vector<int>> A_grid = big_grid_to_small_grid(grid, 0, n / 2, 0, n / 2);
        std::vector<std::vector<int>> B_grid = big_grid_to_small_grid(grid, 0, n / 2, n / 2 + 1, n);
        std::vector<std::vector<int>> C_grid = big_grid_to_small_grid(grid, n / 2 + 1, n, 0, n / 2);
        std::vector<std::vector<int>> D_grid = big_grid_to_small_grid(grid, n / 2 + 1, n, n / 2 + 1, n);

        // check if there is a local minimum in the cross
        if (is_local_min(grid, n / 2, n / 2))
        {
            return grid[n / 2][n / 2];
        }
        else
        {
            std::vector<int> cross_vector(n);
            std::vector<std::vector<int>> cross = {};
            for (int ii = 0; ii < 2; ++ii)
            {
                cross.push_back(cross_vector);
            }
            for (int ii = 0; ii < n; ++ii)
            {
                cross[0][ii] = grid[n / 2][ii];
                cross[1][ii] = grid[ii][n / 2];
            }

            int a = cross[0][std::distance(cross[0].begin(), std::min_element(cross[0].begin(), cross[0].end()))];
            int b = cross[1][std::distance(cross[1].begin(), std::min_element(cross[1].begin(), cross[1].end()))];
            int min;
            if (a >= b)
            {
                min = b;
            }
            else
            {
                min = a;
            }
            int min_pos = std::distance(cross[0].begin(), std::find(cross[0].begin(), cross[0].begin(), min));

            if (min_pos >= 0)
            {
                if (grid[n / 2 - 1][min_pos] > cross[0][min_pos] && grid[n / 2 + 1][min_pos] > cross[0][min_pos])
                {
                    return cross[0][min_pos];
                }
                else if (min_pos < n / 2 + 1)
                {
                    if (grid[n / 2 - 1][min_pos] >= grid[n / 2 + 1][min_pos])
                    {
                        return local_min(C_grid);
                    }
                    else
                    {
                        return local_min(A_grid);
                    }
                }
                else
                {
                    if (grid[n / 2 - 1][min_pos] >= grid[n / 2 + 1][min_pos])
                    {
                        return local_min(D_grid);
                    }
                    else
                    {
                        return local_min(B_grid);
                    }
                }
            }
            else
            {
                min_pos = std::distance(cross[1].begin(), std::find(cross[1].begin(), cross[1].begin(), min));

                if (grid[min_pos][n / 2 - 1] > cross[1][min_pos] && grid[min_pos][n / 2 + 1] > cross[1][min_pos])
                {
                    return cross[1][min_pos];
                }
                else if (min_pos < n / 2 + 1)
                {
                    if (grid[min_pos][n / 2 - 1] >= grid[min_pos][n / 2 + 1])
                    {
                        return local_min(B_grid);
                    }
                    else
                    {
                        return local_min(A_grid);
                    }
                }
                else
                {
                    if (grid[min_pos][n / 2 - 1] >= grid[min_pos][n / 2 + 1])
                    {
                        return local_min(D_grid);
                    }
                    else
                    {
                        return local_min(C_grid);
                    }
                }
            }
        }
    }
}

// main function
int main()
{
    // initialise a 2D grid of random integer values
    std::random_device rd;
    std::mt19937 g(rd());

    const int vector_size = 9;
    std::vector<int> vector_grid(vector_size * vector_size);
    for (int ii = 0; ii < vector_size * vector_size; ++ii)
    {
        vector_grid[ii] = ii;
    }
    std::shuffle(vector_grid.begin(), vector_grid.end(), g);

    std::vector<int> vector_row(vector_size);
    std::vector<std::vector<int>> grid = {};
    for (int ii = 0; ii < vector_size; ++ii)
    {
        grid.push_back(vector_row);

        for (int jj = 0; jj < vector_size; ++jj)
        {
            grid[ii][jj] = vector_grid[ii * vector_size + jj];
        }
    }

    // find the local minimum of the grid with a divide-conquer algorithm
    int min_grid = local_min(grid);

    // output results
    std::cout << "A local minimum of the input grid is " << min_grid << std::endl;
    
    return 0;
}