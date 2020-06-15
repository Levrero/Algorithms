#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>

// partition function
void partition(std::vector<int> &vector, int &pivot)
{
    int temp = vector[pivot];
    vector[pivot] = vector[0];
    vector[0] = temp;

    int ii = 1;
    for (int jj = 1; jj < vector.size(); ++jj)
    {
        if (vector[jj] < vector[0])
        {
            temp = vector[ii];
            vector[ii] = vector[jj];
            vector[jj] = temp;
            ++ii;
        }
    }

    temp = vector[ii - 1];
    vector[ii - 1] = vector[0];
    vector[0] = temp;

    pivot = ii - 1;
}

// choose pivot function (uniform randomly)
int choose_pivot(int n)
{
    srand(time(0));
    
    return rand() % n;
}

// choose pivot function (median of three)
int median_of_three(const std::vector<int> &vector)
{
    int n = vector.size();

    int first_element = vector[0];
    int last_element = vector[n - 1];
    int middle_element;
    if (n < 3)
    {
        middle_element = vector[0];
    }
    else
    {       
        middle_element = n % 2 == 0 ? vector[n / 2 - 1] : vector[n / 2];   
    }

    int median = std::max(std::min(first_element, middle_element), 
        std::min(std::max(first_element, middle_element), last_element));

    auto median_pos = std::find(vector.begin(), vector.end(), median);

    return std::distance(vector.begin(), median_pos);
}

// quick-sort function
std::vector<int> quick_sort(std::vector<int> &unsorted_vector, int &number_inversions)
{
    int n = unsorted_vector.size();

    if (n <= 1)
    {
        return unsorted_vector;
    }
    else
    {
        // choose pivot (random uniformly)
        //int pivot = choose_pivot(n);

        // choose pivot (first element)
        //int pivot = 0;

        // choose pivot (last element)
        //int pivot = n - 1;

        // choose pivot (median of 3)
        int pivot = median_of_three(unsorted_vector);

        partition(unsorted_vector, pivot);

        std::vector<int> unsorted_vector_1 = std::vector<int>(unsorted_vector.begin(), unsorted_vector.begin() + pivot);
        std::vector<int> unsorted_vector_2 = std::vector<int>(unsorted_vector.begin() + pivot + 1, unsorted_vector.end());

        int size = unsorted_vector_1.size();
        if (size > 1)
        {
            number_inversions += size - 1;
        }
        std::vector<int> sorted_vector_1 = quick_sort(unsorted_vector_1, number_inversions);

        size = unsorted_vector_2.size();
        if (size > 1)
        {
            number_inversions += size - 1;
        }
        std::vector<int> sorted_vector_2 = quick_sort(unsorted_vector_2, number_inversions);

        sorted_vector_1.push_back(unsorted_vector[pivot]);
        sorted_vector_1.insert(sorted_vector_1.end(), sorted_vector_2.begin(), sorted_vector_2.end());

        return sorted_vector_1;
    }
}

// main function
int main()
{
    // read vector from file
    std::fstream myfile("input.txt", std::ios_base::in);

    std::vector<int> input_vector = {};
    int input_integer;
    while (myfile >> input_integer)
    {
        input_vector.push_back(input_integer);
    }

    // sort the elements of the vector
    int number_inversions = input_vector.size() - 1;
    std::vector<int> sorted_vector = quick_sort(input_vector, number_inversions);

    // output results
    for (int ii = 0; ii < sorted_vector.size(); ++ii)
    {
        std::cout << "Sorted vector[" << ii << "] is " << sorted_vector[ii] << std::endl;
    }

    std::cout << "The total number of comparisons made by quick-sort is " << number_inversions << std::endl;

    return 0;
}