#include <iostream>
#include <fstream>
#include <vector>

// split inversion counting function (where the inversion is split on both halves of the input vector)
std::pair<unsigned long int, std::vector<int>> inversion_counting_split(const std::vector<int> &input_vector_1, 
    const std::vector<int> &input_vector_2)
{
    int size_1 = input_vector_1.size();
    int size_2 = input_vector_2.size();
    int total_size = size_1 + size_2;

    std::vector<int> sorted_vector(total_size);

    unsigned long int number_inversions = 0;

    int ii = 0, jj = 0;
    for (int kk = 0; kk < total_size; ++kk)
    {
        if (ii >= size_1)
        {
            sorted_vector[kk] = input_vector_2[jj];
            ++jj;
        }
        else if (jj >= size_2)
        {
            sorted_vector[kk] = input_vector_1[ii];
            ++ii;
        }
        else if (input_vector_1[ii] < input_vector_2[jj])
        {
            sorted_vector[kk] = input_vector_1[ii];
            ++ii;
        }
        else
        {
            sorted_vector[kk] = input_vector_2[jj];
            number_inversions += (size_1 - ii);
            ++jj;
        }
    }

    return {number_inversions, sorted_vector};
}

// inversion counting function
std::pair<unsigned long int, std::vector<int>> inversion_counting(const std::vector<int> &input_vector)
{
    int n = input_vector.size();

    if (n == 1)
    {
        return {0, input_vector};
    }
    else
    {
        auto [x, sorted_vector_1] = inversion_counting(std::vector<int>(input_vector.begin(), input_vector.begin() + n / 2));
        auto [y, sorted_vector_2] = inversion_counting(std::vector<int>(input_vector.begin() + n / 2, input_vector.end()));
        auto [z, sorted_vector] = inversion_counting_split(sorted_vector_1, sorted_vector_2);

        return {x + y + z, sorted_vector};
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

    // count the number of inversions
    auto [number_inversions, sorted_input_vector] = inversion_counting(input_vector);

    // output results
    std::cout << "The number of inversions is " << number_inversions << std::endl;

    return 0;
}