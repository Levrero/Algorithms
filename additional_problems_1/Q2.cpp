#include <iostream>
#include <vector>
#include <time.h>

// merge function
std::vector<int> merge(const std::vector<int> &sorted_vector_1, const std::vector<int> &sorted_vector_2)
{
    int size_1 = sorted_vector_1.size();
    int size_2 = sorted_vector_2.size();
    int total_size = size_1 + size_2;

    std::vector<int> sorted_vector(total_size);

    int ii = 0, jj = 0;
    for (int kk = 0; kk < total_size; ++kk)
    {
        if (ii >= size_1)
        {
            sorted_vector[kk] = sorted_vector_2[jj];
            ++jj;
        }
        else if (jj >= size_2)
        {
            sorted_vector[kk] = sorted_vector_1[ii];
            ++ii;
        }
        else if (sorted_vector_1[ii] < sorted_vector_2[jj])
        {
            sorted_vector[kk] = sorted_vector_1[ii];
            ++ii;
        }
        else
        {
            sorted_vector[kk] = sorted_vector_2[jj];
            ++jj;
        }
    }

    return sorted_vector;
}

// merge-sort function
std::vector<int> merge_sort(const std::vector<int> &unsorted_vector)
{
    int n = unsorted_vector.size();

    if (n <= 1)
    {
        return unsorted_vector;
    }
    else
    {
        std::vector<int> unsorted_vector_1 = std::vector<int>(unsorted_vector.begin(), unsorted_vector.begin() + n / 2);
        std::vector<int> unsorted_vector_2 = std::vector<int>(unsorted_vector.begin() + n / 2, unsorted_vector.end());

        std::vector<int> sorted_vector_1 = merge_sort(unsorted_vector_1);
        std::vector<int> sorted_vector_2 = merge_sort(unsorted_vector_2);

        return merge(sorted_vector_1, sorted_vector_2);
    }
}

// function to find the maximum element of a unimodal vector in O(log n) time
int find_maximum(std::vector<int> &unsorted_vector)
{
    int n = unsorted_vector.size();

    if (n == 1)
    {
        return unsorted_vector[0];
    }
    else
    {
        std::vector<int> unsorted_vector_1 = std::vector<int>(unsorted_vector.begin(), unsorted_vector.begin() + n / 2);
        std::vector<int> unsorted_vector_2 = std::vector<int>(unsorted_vector.begin() + n / 2, unsorted_vector.end());

        int maximum_1 = find_maximum(unsorted_vector_1);
        int maximum_2 = find_maximum(unsorted_vector_2);

        return std::max(maximum_1, maximum_2);
    }
}

// main function
int main()
{
    // initialise two random vectors of random size between 1 and 100
    const int vector_size = 250;
    
    srand(time(0));

    int vector_size_1 = rand() % vector_size + 1;
    int vector_size_2 = rand() % vector_size + 1;

    std::vector<int> unsorted_vector_1(vector_size_1);
    for (int ii = 0; ii < vector_size_1; ++ii)
    {
        unsorted_vector_1[ii] = rand() % vector_size_1 + 1;
    }

    std::vector<int> unsorted_vector_2(vector_size_2);
    for (int ii = 0; ii < vector_size_2; ++ii)
    {
        unsorted_vector_2[ii] = rand() % vector_size_2 + 1;
    }

    // sort the elements of the vectors
    std::vector<int> sorted_vector_1 = merge_sort(unsorted_vector_1);
    std::vector<int> sorted_vector_2 = merge_sort(unsorted_vector_2);

    std::vector<int> temp_vector = sorted_vector_2;
    for (int ii = 0; ii < vector_size_2; ++ii)
    {
        sorted_vector_2[ii] = temp_vector[vector_size_2 - 1 - ii];
    }

    // join the two vectors
    std::vector<int> sorted_vector = sorted_vector_1;
    sorted_vector.insert( sorted_vector.end(), sorted_vector_2.begin(), sorted_vector_2.end() );

    // find maximum element of the unimodal vector
    int maximum_element = find_maximum(sorted_vector);

    // output results
    for (int ii = 0; ii < vector_size_1 + vector_size_2; ++ii)
    {
        std::cout << "Unsorted array[" << ii << "] is " << sorted_vector[ii] << std::endl;
    }
    std::cout << "The maximum element is " << maximum_element << std::endl;

    return 0;
}