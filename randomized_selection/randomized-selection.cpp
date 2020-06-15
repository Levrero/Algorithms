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

// quick-sort function
int randomized_selection(std::vector<int> &unsorted_vector, int statistic)
{
    int n = unsorted_vector.size();

    if (n == 1)
    {
        return unsorted_vector[0];
    }
    else
    {
        // choose pivot (random uniformly)
        int pivot = choose_pivot(n);

        partition(unsorted_vector, pivot);

        if (pivot == statistic)
        {
            return unsorted_vector[pivot];
        }
        else if (pivot > statistic)
        {
            std::vector<int> unsorted_vector_1 = std::vector<int>(unsorted_vector.begin(), unsorted_vector.begin() + pivot);

            return randomized_selection(unsorted_vector_1, statistic);
        }
        else
        {
            std::vector<int> unsorted_vector_2 = std::vector<int>(unsorted_vector.begin() + pivot + 1, unsorted_vector.end());

            return randomized_selection(unsorted_vector_2, statistic - pivot - 1); 
        }
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

    // choose i-th order statistic
    int statistic = 5;

    // sort the elements of the vector
    int selection = randomized_selection(input_vector, statistic);

    // output results
    for (int ii = 0; ii < input_vector.size(); ++ii)
    {
        std::cout << "Unsorted vector[" << ii << "] is " << input_vector[ii] << std::endl;
    }

    std::cout << "The " << statistic << "-th order statistic is " << selection << std::endl;

    return 0;
}