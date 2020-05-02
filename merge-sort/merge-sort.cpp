#include <iostream>

// main function
int main()
{
    // initialise the array to a random value
    int array_size = 100;
    std::array<int, array_size> unsorted_array;
    for (auto &element : unsorted_array)
    {
        element = rand() % array_size + 1;
    }

    // sort the elements of the array
    auto sorted_array = merge_sort(unsorted_array);
}

// merge-sort algorithm
