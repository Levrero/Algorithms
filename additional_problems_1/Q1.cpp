#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <algorithm>
#include <iterator>

// max min function
std::pair<int, int> max_min(const std::vector<int> &vector_input)
{
    return {std::max(vector_input[1], vector_input[0]), std::min(vector_input[1], vector_input[0])};
}

// find second largest element function
std::vector<std::pair<int, int>> find_tuples(const std::vector<int> &unsorted_vector, int &count)
{
    int n = unsorted_vector.size();

    if (n == 2)
    {   
        ++count;
        return {max_min(unsorted_vector)};
    }
    else
    {
        std::vector<int> unsorted_vector_1 = std::vector<int>(unsorted_vector.begin(), unsorted_vector.begin() + n / 2);
        std::vector<int> unsorted_vector_2 = std::vector<int>(unsorted_vector.begin() + n / 2, unsorted_vector.end());

        auto tuple_vector_1 = find_tuples(unsorted_vector_1, count);
        auto tuple_vector_2 = find_tuples(unsorted_vector_2, count);

        ++count;
        std::vector<std::pair<int, int>> tuple_vector = {};
        if (tuple_vector_1[0].first > tuple_vector_2[0].first)
        {
            for (int ii = 0; ii < tuple_vector_1.size(); ++ii)
            {
                tuple_vector.push_back(tuple_vector_1[ii]);
            }

            tuple_vector_2[0].second = tuple_vector_2[0].first;
            tuple_vector_2[0].first = tuple_vector_1[0].first; 

            tuple_vector.push_back(tuple_vector_2[0]);
        }
        else
        {
            tuple_vector_1[0].second = tuple_vector_1[0].first;
            tuple_vector_1[0].first = tuple_vector_2[0].first; 

            tuple_vector.push_back(tuple_vector_1[0]);

            for (int ii = 0; ii < tuple_vector_1.size(); ++ii)
            {
                tuple_vector.push_back(tuple_vector_2[ii]);
            }
        }
        
        return tuple_vector;
    }
}

// compare tuples and obtain the second largest element
int compare_tuples(const std::vector<std::pair<int, int>> &tuple_vector, int &count)
{
    int max = 0;

    ++count;
    if (tuple_vector[0].second > tuple_vector[1].second)   
    { 
        max = tuple_vector[0].second;
    }   
    else
    { 
        max = tuple_vector[1].second; 
    }     
  
    for (int ii = 2; ii < tuple_vector.size(); ++ii) 
    { 
        ++count;
        if (tuple_vector[ii].second >  max)
        {       
            max = tuple_vector[ii].second;
        } 
    } 
    
    return max;
}

// main function
int main()
{
    // initialise the vector to a random value (must be a power of 2)
    const int vector_size = 256;
    std::vector<int> unsorted_vector(vector_size);
    for (int ii = 0; ii < vector_size; ++ii)
    {
        unsorted_vector[ii] = ii;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), g);

    copy(unsorted_vector.begin(), unsorted_vector.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    // obtain the second largest element
    int count = 0;
    auto tuple_vector = find_tuples(unsorted_vector, count);
    int second_largest = compare_tuples(tuple_vector, count);

    // output results
    for (int ii = 0; ii < tuple_vector.size(); ++ii)
    {
        std::cout << "tuple[" << ii << ", 1] is " << tuple_vector[ii].first << std::endl;
        std::cout << "tuple[" << ii << ", 2] is " << tuple_vector[ii].second << std::endl;
    }

    std::cout << "The second largest element in the given array is " << second_largest << std::endl;
    
    std::cout << "The total number of operations is " << count << std::endl;

    std::cout << "The correct number of operations is " << vector_size + std::log(vector_size) / std::log(2) - 2 << std::endl;

    return 0;
}