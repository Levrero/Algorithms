#include <iostream>
#include <string>

using namespace std;

// function to count the number of elements in a string array
int size_of_array(const string input_string)
{
    int count = 0;
    for (int ii = 0; input_string[ii]; ++ii)
    {
        ++count;
    }

    return count;
}

// function to sum strings (assume the inputs are valid strings with numerical values)
string string_sum(const string input_1, const string input_2)
{
    int size_1 = size_of_array(input_1);
    int size_2 = size_of_array(input_2);
    int size = max(size_1, size_2) + 1;
    string sum(size, '0');

    // make sizes of arrays consistent
    string string_1 = string(size - size_1, '0') + input_1;
    string string_2 = string(size - size_2, '0') + input_2;

    // summation loop
    for (int ii = size - 1; ii >= 0; --ii)
    {   
        int temp = (string_1[ii] - '0') + (string_2[ii] - '0') + (sum[ii] - '0');
        if (temp >= 10 && ii > 0)
        {   
            sum[ii - 1] = to_string(temp)[0];
            sum[ii] = to_string(temp)[1];
        }
        else
        {
            sum[ii] = to_string(temp)[0];
        }
    }

    // get rid of unnecessary extra zeroes at the beginning
    int ii = 0;
    size = size_of_array(sum);
    while (ii < size)
    {
        if (sum[0] == '0')
        {
            sum = sum.substr(1);
        }
        ++ii;
        size = size_of_array(sum);
    }

    return sum;
}

//function to substract strings (assume the inputs are valid strings with numerical values)
string string_substract(const string input_1, const string input_2)
{
    int size_1 = size_of_array(input_1);
    int size_2 = size_of_array(input_2);
    int size = max(size_1, size_2);
    string substract(size, '0');

    // make sizes of arrays consistent
    string string_1 = string(size - size_1, '0') + input_1;
    string string_2 = string(size - size_2, '0') + input_2;

    // substraction loop
    int carry_on = 0;
    for (int ii = size - 1; ii >= 0; --ii)
    {
        int temp = (string_1[ii] - '0') - (string_2[ii] - '0') - carry_on;

        carry_on = 0;

        if (temp < 0)
        {
            temp += 10;
            substract[ii] = to_string(temp)[0];
            ++carry_on;
        }
        else
        {   
            substract[ii] = to_string(temp)[0];
        }
    }

    // get rid of unnecessary extra zeroes at the beginning
    int ii = 0;
    size = size_of_array(substract);
    while (ii < size)
    {
        if (substract[0] == '0')
        {
            substract = substract.substr(1);
        }
        ++ii;
        size = size_of_array(substract);
    }

    return substract;     
}

// karatsuba multiplication function
string karatsuba_multiplication(const string input_1, const string input_2)
{
    int size_1 = size_of_array(input_1);
    int size_2 = size_of_array(input_2);
    int n = max(size_1, size_2);

    // make sizes of arrays consistent
    string string_1 = string(n - size_1, '0') + input_1;
    string string_2 = string(n - size_2, '0') + input_2;

    if (n == 1)
    {
        return to_string((input_1[0] - '0') * (input_2[0] - '0'));
    }

    // compute a, b, c and d
    string a = string_1.substr(0, n / 2);
    string b = string_1.substr(n / 2, n - n / 2);
    string c = string_2.substr(0, n / 2);
    string d = string_2.substr(n / 2, n - n / 2);

    string ac = karatsuba_multiplication(a, c);
    string bd = karatsuba_multiplication(b, d);
    string abcd = karatsuba_multiplication(string_sum(a, b), string_sum(c, d));
    string adbc = string_substract(abcd, string_sum(ac, bd));
        
    string str1 = ac + string(2 * (n - n / 2), '0');
    string str2 = adbc + string(n - n / 2, '0');

    string output = string_sum(string_sum(str1, str2), bd);

    return output;
}

// main function
int main()
{
    // initialise inputs
    string input_1 = "3141592653589793238462643383279502884197169399375105820974944592";
    string input_2 = "2718281828459045235360287471352662497757247093699959574966967627";

    // compute the output
    string output = karatsuba_multiplication(input_1, input_2);

    // output result
    cout << "The output value is " << output << endl;
    
    return 0;
}