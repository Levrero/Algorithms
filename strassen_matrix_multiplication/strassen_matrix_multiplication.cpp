#include <iostream>
#include <vector>

// naive matrix multiplication function
std::vector<std::vector<int>> naive_matrix_multiplication(const std::vector<std::vector<int>> &matrix_input_1,
    const std::vector<std::vector<int>> &matrix_input_2)
{
    int m = matrix_input_1.size();
    int p = matrix_input_2.size();
    int n = matrix_input_2[0].size();

    std::vector<std::vector<int>> matrix_result(n);
    for (int ii = 0; ii < m; ++ii)
    {
        matrix_result[ii].resize(n, 0);
    }

    for (int ii = 0; ii < m; ++ii)
    {
        for (int jj = 0; jj < n; ++jj)
        {
            for (int kk = 0; kk < p; ++kk)
            {
                matrix_result[ii][jj] += matrix_input_1[ii][kk] * matrix_input_2[kk][jj];
            }
        }
    }

    return matrix_result;
}

// function which performs addition and substraction of two matrices
std::vector<std::vector<int>> matrix_addition_substraction(const std::vector<std::vector<int>> &matrix_input_1,
    const std::vector<std::vector<int>> &matrix_input_2, bool substraction_flag)
{
    int m = matrix_input_1.size();
    int n = matrix_input_1[0].size();
    std::vector<std::vector<int>> matrix_result(m);
    
    for (int ii = 0; ii < m; ++ii)
    {
        matrix_result[ii].resize(n, 0);
    }

    if (substraction_flag)
    {
        for (int ii = 0; ii < m; ++ii)
        {
            for (int jj = 0; jj < n; ++jj)
            {
                matrix_result[ii][jj] = matrix_input_1[ii][jj] - matrix_input_2[ii][jj];
            }
        }
    }
    else
    {
        for (int ii = 0; ii < m; ++ii)
        {
            for (int jj = 0; jj < n; ++jj)
            {
                matrix_result[ii][jj] = matrix_input_1[ii][jj] + matrix_input_2[ii][jj];
            }
        }
    }
    
    return matrix_result;
}

// function which copies a small matrix into a big matrix
void matrix_copy_small_to_big(std::vector<std::vector<int>> &big_matrix, const std::vector<std::vector<int>> &small_matrix,
    int initial_row, int final_row, int initial_col, int final_col)
{
    for (int ii = initial_row; ii < final_row; ++ii)
    {
        for (int jj = initial_col; jj < final_col; ++jj)
        {
            big_matrix[ii][jj] = small_matrix[ii - initial_row][jj - initial_col];
        }
    }
}

// function which copies a part of a big matrix into a small matrix
void matrix_copy_big_to_small(const std::vector<std::vector<int>> &big_matrix, std::vector<std::vector<int>> &small_matrix,
    int initial_row, int final_row, int initial_col, int final_col)
{
    small_matrix.resize(final_row - initial_row);

    for (int ii = 0; ii < final_row - initial_row; ++ii)
    {
        small_matrix[ii].resize(final_col - initial_col);
    }

    for (int ii = 0; ii < small_matrix.size(); ++ii)
    {
        for (int jj = 0; jj < small_matrix[0].size(); ++jj)
        {
            small_matrix[ii][jj] = big_matrix[ii + initial_row][jj + initial_col];
        }
    }
}

// inversion counting function
std::vector<std::vector<int>> strassen_matrix_multiplication(const std::vector<std::vector<int>> &input_matrix_1,
    const std::vector<std::vector<int>> &input_matrix_2)
{
    int m = input_matrix_1.size();
    int p = input_matrix_2.size();
    int n = input_matrix_2[0].size();

    if (m == 1 || p == 1 || n == 1)
    {
        return naive_matrix_multiplication(input_matrix_1, input_matrix_2);
    }
    else
    {
        // create and initialize the different matrices needed for Strassen's algorithm
        std::vector<std::vector<int>> A = {};
        matrix_copy_big_to_small(input_matrix_1, A, 0, m / 2, 0, p / 2);

        std::vector<std::vector<int>> B = {};
        matrix_copy_big_to_small(input_matrix_1, B, 0, m / 2, p / 2, p);

        std::vector<std::vector<int>> C = {};
        matrix_copy_big_to_small(input_matrix_1, C, m / 2, m, 0, p / 2);

        std::vector<std::vector<int>> D = {};
        matrix_copy_big_to_small(input_matrix_1, D, m / 2, m, p / 2, p);

        std::vector<std::vector<int>> E = {};
        matrix_copy_big_to_small(input_matrix_2, E, 0, p / 2, 0, n / 2);

        std::vector<std::vector<int>> F = {};
        matrix_copy_big_to_small(input_matrix_2, F, 0, p / 2, n / 2, n);

        std::vector<std::vector<int>> G = {};
        matrix_copy_big_to_small(input_matrix_2, G, p / 2, p, 0, n / 2);

        std::vector<std::vector<int>> H = {};
        matrix_copy_big_to_small(input_matrix_2, H, p / 2, p, n / 2, n);

        std::vector<std::vector<int>> P1 = strassen_matrix_multiplication(A, matrix_addition_substraction(F, H, true));
        std::vector<std::vector<int>> P2 = strassen_matrix_multiplication(matrix_addition_substraction(A, B, false), H);
        std::vector<std::vector<int>> P3 = strassen_matrix_multiplication(matrix_addition_substraction(C, D, false), E);
        std::vector<std::vector<int>> P4 = strassen_matrix_multiplication(D, matrix_addition_substraction(G, E, true));
        std::vector<std::vector<int>> P5 = strassen_matrix_multiplication(matrix_addition_substraction(A, D, false), matrix_addition_substraction(E, H, false));
        std::vector<std::vector<int>> P6 = strassen_matrix_multiplication(matrix_addition_substraction(B, D, true), matrix_addition_substraction(G, H, false));
        std::vector<std::vector<int>> P7 = strassen_matrix_multiplication(matrix_addition_substraction(A, C, true), matrix_addition_substraction(E, F, false));

        std::vector<std::vector<int>> R1 = matrix_addition_substraction(matrix_addition_substraction(matrix_addition_substraction(P5, P4, false), P2, true), P6, false);
        std::vector<std::vector<int>> R2 = matrix_addition_substraction(P1, P2, false);
        std::vector<std::vector<int>> R3 = matrix_addition_substraction(P3, P4, false);
        std::vector<std::vector<int>> R4 = matrix_addition_substraction(matrix_addition_substraction(matrix_addition_substraction(P1, P5, false), P3, true), P7, true);
        
        std::vector<std::vector<int>> matrix_result(m);
        for (int ii = 0; ii < m; ++ii)
        {
            matrix_result[ii].resize(n, 0);
        }

        matrix_copy_small_to_big(matrix_result, R1, 0, m / 2, 0, p / 2);
        matrix_copy_small_to_big(matrix_result, R2, 0, m / 2, p / 2, p);
        matrix_copy_small_to_big(matrix_result, R3, m / 2, m, 0, p / 2);
        matrix_copy_small_to_big(matrix_result, R4, m / 2, m, p / 2, p);

        return matrix_result;
    }
}

// main function
int main()
{
    // create two random matrices with consistent dimensions so that they can be multiplied
    const int m = 8;
    const int p = 8;
    const int n = m;
    std::vector<std::vector<int>> matrix_1(m);
    std::vector<std::vector<int>> matrix_2(p);

    for (int ii = 0; ii < m; ++ii)
    {
        matrix_1[ii].resize(p, 0);
        for (int jj = 0; jj < p; ++jj)
        {
            matrix_1[ii][jj] = rand() % 100 + 1;
        }
    }

    for (int ii = 0; ii < p; ++ii)
    {
        matrix_2[ii].resize(n, 0);
        for (int jj = 0; jj < n; ++jj)
        {
            matrix_2[ii][jj] = rand() % 100 + 1;
        }
    }

    // matrix multiplication through Strassen's method
    std::vector<std::vector<int>> matrix_result_strassen = strassen_matrix_multiplication(matrix_1, matrix_2);

    // matrix multiplication through the naive matrix multiplication algorithm
    std::vector<std::vector<int>> matrix_result_naive = naive_matrix_multiplication(matrix_1, matrix_2);

    // output results
    for (int ii = 0; ii < m; ++ii)
    {
        for (int jj = 0; jj < n; ++jj)
        {
            std::cout << "matrix_result_strassen[" << ii << "," << jj << "] is " << matrix_result_strassen[ii][jj] << std::endl;
        }
    }

    for (int ii = 0; ii < m; ++ii)
    {
        for (int jj = 0; jj < n; ++jj)
        {
            std::cout << "matrix_result_naive[" << ii << "," << jj << "] is " << matrix_result_naive[ii][jj] << std::endl;
        }
    }

    return 0;
}