#include <iostream>
#include <vector>
#include <random>
#include <float.h>

// simple Euclidean distance function
double distance(double x1, double x2, double y1, double y2)
{
    return std::sqrt(std::pow(x2 - x1, 2.0) + std::pow(y2 - y1, 2.0));
}

// naive closest pair function
std::pair<std::vector<double>, std::vector<double>> naive_closest_pair(const std::vector<double> &x_coords, const std::vector<double> &y_coords)
{
    double dist0 = DBL_MAX;
    std::vector<double> closest_x_coords(2);
    std::vector<double> closest_y_coords(2);
    for (int ii = 0; ii < x_coords.size() - 1; ++ii)
    {
        for (int jj = ii + 1; jj < x_coords.size(); ++jj)
        {
            double dist = distance(x_coords[jj], x_coords[ii], y_coords[jj], y_coords[ii]);
            if (dist < dist0)
            {
                dist0 = dist;
                closest_x_coords = {x_coords[jj], x_coords[ii]};
                closest_y_coords = {y_coords[jj], y_coords[ii]};
            }
        }
    }

    return {closest_x_coords, closest_y_coords};
}

// merge function
std::pair<std::vector<double>, std::vector<double>> merge(const std::vector<double> &sorted_x_coords_1, const std::vector<double> &sorted_x_coords_2,
    const std::vector<double> &sorted_y_coords_1, const std::vector<double> &sorted_y_coords_2, int sorting_array_num)
{
    int size_1 = sorted_x_coords_1.size();
    int size_2 = sorted_x_coords_2.size();
    int total_size = size_1 + size_2;

    std::vector<double> sorted_x_coords(total_size);
    std::vector<double> sorted_y_coords(total_size);

    int ii = 0, jj = 0;
    if (sorting_array_num == 0)
    {
        for (int kk = 0; kk < total_size; ++kk)
        {
            if (ii >= size_1)
            {
                sorted_x_coords[kk] = sorted_x_coords_2[jj];
                sorted_y_coords[kk] = sorted_y_coords_2[jj];
                ++jj;
            }
            else if (jj >= size_2)
            {
                sorted_x_coords[kk] = sorted_x_coords_1[ii];
                sorted_y_coords[kk] = sorted_y_coords_1[ii];
                ++ii;
            }
            else if (sorted_x_coords_1[ii] < sorted_x_coords_2[jj])
            {
                sorted_x_coords[kk] = sorted_x_coords_1[ii];
                sorted_y_coords[kk] = sorted_y_coords_1[ii];
                ++ii;
            }
            else
            {
                sorted_x_coords[kk] = sorted_x_coords_2[jj];
                sorted_y_coords[kk] = sorted_y_coords_2[jj];
                ++jj;
            }
        }
    }
    else
    {
        for (int kk = 0; kk < total_size; ++kk)
        {
            if (ii >= size_1)
            {
                sorted_x_coords[kk] = sorted_x_coords_2[jj];
                sorted_y_coords[kk] = sorted_y_coords_2[jj];
                ++jj;
            }
            else if (jj >= size_2)
            {
                sorted_x_coords[kk] = sorted_x_coords_1[ii];
                sorted_y_coords[kk] = sorted_y_coords_1[ii];
                ++ii;
            }
            else if (sorted_y_coords_1[ii] < sorted_y_coords_2[jj])
            {
                sorted_x_coords[kk] = sorted_x_coords_1[ii];
                sorted_y_coords[kk] = sorted_y_coords_1[ii];
                ++ii;
            }
            else
            {
                sorted_x_coords[kk] = sorted_x_coords_2[jj];
                sorted_y_coords[kk] = sorted_y_coords_2[jj];
                ++jj;
            }
        }
    }

    return {sorted_x_coords, sorted_y_coords};
}

// merge-sort function
std::pair<std::vector<double>, std::vector<double>> merge_sort(const std::vector<double> &unsorted_x_coords, 
    const std::vector<double> &unsorted_y_coords, int sorting_array_num)
{
    int n = unsorted_x_coords.size();

    if (n <= 1)
    {
        return {unsorted_x_coords, unsorted_y_coords};
    }
    else
    {
        std::vector<double> unsorted_x_coords_1 = std::vector<double>(unsorted_x_coords.begin(), unsorted_x_coords.begin() + n / 2);
        std::vector<double> unsorted_x_coords_2 = std::vector<double>(unsorted_x_coords.begin() + n / 2, unsorted_x_coords.end());

        std::vector<double> unsorted_y_coords_1 = std::vector<double>(unsorted_y_coords.begin(), unsorted_y_coords.begin() + n / 2);
        std::vector<double> unsorted_y_coords_2 = std::vector<double>(unsorted_y_coords.begin() + n / 2, unsorted_y_coords.end());

        auto [sorted_x_coords_1, sorted_y_coords_1] = merge_sort(unsorted_x_coords_1, unsorted_y_coords_1, sorting_array_num);
        auto [sorted_x_coords_2, sorted_y_coords_2] = merge_sort(unsorted_x_coords_2, unsorted_y_coords_2, sorting_array_num);

        return merge(sorted_x_coords_1, sorted_x_coords_2, sorted_y_coords_1, sorted_y_coords_2, sorting_array_num);
    }    
}

// return the pair of points with the smallest distance
std::pair<std::vector<double>, std::vector<double>> best_of_three(const std::vector<double> &x1, const std::vector<double> &y1, 
    const std::vector<double> &x2, const std::vector<double> &y2, const std::vector<double> &x3, const std::vector<double> &y3)
{
    double d1 = DBL_MAX;
    double d2 = DBL_MAX;
    double d3 = DBL_MAX;
    if (x1.size() != 0)
    {
        d1 = std::sqrt(std::pow(x1[1] - x1[0], 2) + std::pow(y1[1] - y1[0], 2));
    }
    if (x2.size() != 0)
    {
        d2 = std::sqrt(std::pow(x2[1] - x2[0], 2) + std::pow(y2[1] - y2[0], 2));
    }
    if (x3.size() != 0)
    {
        d3 = std::sqrt(std::pow(x3[1] - x3[0], 2) + std::pow(y3[1] - y3[0], 2));
    }

    if (d1 <= d2 && d1 <= d3)
    {
        return {x1, y1};
    }
    else if (d2 <= d1 && d2 <= d3)
    {
        return {x2, y2};
    }
    else
    {
        return {x3, y3};
    }
}

// closest split pair function
std::pair<std::vector<double>, std::vector<double>> closest_split_pair(const std::vector<double> x_Px, const std::vector<double> y_Px,
    const std::vector<double> x_Py, const std::vector<double> y_Py, double delta)
{
    int n = x_Px.size();

    double x_median = x_Px[n / 2];
    double y_median = y_Px[n / 2];

    std::vector<double> x_Sy = {};
    std::vector<double> y_Sy = {};
    for (int ii = 0; ii < n; ++ii)
    {
        if (x_Py[ii] >= x_median - delta && x_Py[ii] <= x_median + delta)
        {
            x_Sy.push_back(x_Py[ii]);
            y_Sy.push_back(y_Py[ii]);
        }
    }
    
    double best = delta;
    std::vector<double> x_best_pair = {};
    std::vector<double> y_best_pair = {};
    for (int ii = 0; ii < x_Sy.size() - 1; ++ii)
    {
        for (int jj = ii + 1; jj < ii + std::min(7, (int)x_Sy.size() - ii); ++jj)
        {
            double dist = distance(x_Sy[jj], x_Sy[ii], y_Sy[jj], y_Sy[ii]);
            if (dist < best)
            {
                best = dist;
                if (x_best_pair.size() == 0)
                {
                    x_best_pair.push_back(x_Sy[jj]);
                    x_best_pair.push_back(x_Sy[ii]);
                    y_best_pair.push_back(y_Sy[jj]);
                    y_best_pair.push_back(y_Sy[ii]);
                }
                else
                {
                    x_best_pair = {x_Sy[jj], x_Sy[ii]};
                    y_best_pair = {y_Sy[jj], y_Sy[ii]};
                }
            }
        }
    }
    
    return {x_best_pair, y_best_pair};
}

// closest pair function
std::pair<std::vector<double>, std::vector<double>> closest_pair(const std::vector<double> x_Px, const std::vector<double> y_Px,
    const std::vector<double> x_Py, const std::vector<double> y_Py)
{
    int n = x_Px.size();

    if (n <= 3)
    {
        return naive_closest_pair(x_Px, y_Px);
    }
    else
    {
        std::vector<double> x_Qx = std::vector<double>(x_Px.begin(), x_Px.begin() + n / 2);
        std::vector<double> x_Rx = std::vector<double>(x_Px.begin() + n / 2, x_Px.end());

        std::vector<double> y_Qx = std::vector<double>(y_Px.begin(), y_Px.begin() + n / 2);
        std::vector<double> y_Rx = std::vector<double>(y_Px.begin() + n / 2, y_Px.end());

        std::vector<double> x_Qy = {};
        std::vector<double> y_Qy = {};

        std::vector<double> x_Ry = {};
        std::vector<double> y_Ry = {};
        
        for (int ii = 0; ii < n; ++ii)
        {
            if (x_Py[ii] < x_Px[n / 2])
            {
                x_Qy.push_back(x_Py[ii]);
                y_Qy.push_back(y_Py[ii]);
            }
            else
            {
                x_Ry.push_back(x_Py[ii]);
                y_Ry.push_back(y_Py[ii]);
            }
        }

        auto [x_coords_closest_1, y_coords_closest_1] = closest_pair(x_Qx, y_Qx, x_Qy, y_Qy);
        auto [x_coords_closest_2, y_coords_closest_2] = closest_pair(x_Rx, y_Rx, x_Ry, y_Ry);
        
        double delta = std::min(distance(x_coords_closest_1[1], x_coords_closest_1[0], y_coords_closest_1[1], y_coords_closest_1[0]), 
            distance(x_coords_closest_2[1], x_coords_closest_2[0], y_coords_closest_2[1], y_coords_closest_2[0]));

        auto [x_coords_closest_3, y_coords_closest_3] = closest_split_pair(x_Px, y_Px, x_Py, y_Py, delta);

        return best_of_three(x_coords_closest_1, y_coords_closest_1, x_coords_closest_2, y_coords_closest_2,
            x_coords_closest_3, y_coords_closest_3);
    }
}

// main function
int main()
{
    // initialise the vectors to pairs of random values
    const int vector_size = 10;

    std::uniform_real_distribution<double> unif(0,vector_size);
    std::default_random_engine re;

    std::vector<double> x_coords(vector_size);
    std::vector<double> y_coords(vector_size);
    for (int ii = 0; ii < vector_size; ++ii)
    {
        x_coords[ii] = unif(re);
        y_coords[ii] = unif(re);
    }

    // sort the X and Y coordinates
    auto [x_coords_xsorted, y_coords_xsorted] = merge_sort(x_coords, y_coords, 0);
    auto [x_coords_ysorted, y_coords_ysorted] = merge_sort(x_coords, y_coords, 1);

    // find the closest pair
    auto [x_coords_closest, y_coords_closest] = closest_pair(x_coords_xsorted, y_coords_xsorted, x_coords_ysorted, y_coords_ysorted);

    // output results
    std::cout << "The points in consideration are:" << std::endl;
    for (int ii = 0; ii < vector_size; ++ii)
    {
        std::cout << "X coordinates [" << ii << "]: " << x_coords[ii] << std::endl;
        std::cout << "Y coordinates [" << ii << "]: " << y_coords[ii] << std::endl;        
    }

    std::cout << "The two points which are closest are have X coordinates " << x_coords_closest[0] <<
        " and " << x_coords_closest[1] << ", and Y coordinates " << y_coords_closest[0] << " and " <<
        y_coords_closest[1] << std::endl;
    
    // find the closest pair with the naive algorithm
    auto [x_coords_closest_naive, y_coords_closest_naive] = naive_closest_pair(x_coords, y_coords);

    // output naive results
    std::cout << "The two points which are closest (with the naive algorithm) are have X coordinates " << x_coords_closest_naive[0] <<
        " and " << x_coords_closest_naive[1] << ", and Y coordinates " << y_coords_closest_naive[0] << " and " <<
        y_coords_closest_naive[1] << std::endl;


    return 0;
}