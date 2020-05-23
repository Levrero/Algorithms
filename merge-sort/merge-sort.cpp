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

// main function
int main()
{
    // initialise the vector to a random value
    const int vector_size = 100;
    std::vector<int> unsorted_vector(vector_size);

    srand(time(0));

    for (int ii = 0; ii < vector_size; ++ii)
    {
        unsorted_vector[ii] = rand() % vector_size + 1;
    }

    // sort the elements of the vector
    std::vector<int> sorted_vector = merge_sort(unsorted_vector);

    // output results
    for (int ii = 0; ii < vector_size; ++ii)
    {
        std::cout << "Sorted vector[" << ii << "] is " << sorted_vector[ii] << std::endl;
    }

    return 0;
}